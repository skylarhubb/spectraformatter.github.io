#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <unordered_set>
#include <unordered_map>

std::string removeDuplicates(const std::string& paragraph) {
    std::string result;
    std::unordered_map<std::string, std::string> speeches;
    std::string speaker;

    std::istringstream iss(paragraph);
    std::string line;

    while (std::getline(iss, line)) {
        std::string currentSpeaker = line.substr(0, line.find(':') + 1);
        std::string speech = line.substr(line.find(':') + 1);

        if (currentSpeaker != speaker) {
            result += "\n" + line;
            speeches[currentSpeaker] = speech;
        } else {
            if (speech != speeches[currentSpeaker]) {
                result += " " + speech;
                speeches[currentSpeaker] = speech;
            }
        }

        speaker = currentSpeaker;
    }

    return result;
}

int main() {
    // Open the input file
    std::ifstream inputFile("input.txt");
    if (!inputFile) {
        std::cerr << "Failed to open input file." << std::endl;
        return 1;
    }

    // Create the output file
    std::ofstream outputFile("output.txt");
    if (!outputFile) {
        std::cerr << "Failed to create output file." << std::endl;
        return 1;
    }

    // Read the file line by line
    std::string line;
    std::string outputText;
    std::regex numberRegex("\\d+");
    std::regex arrowRegex(" --> ");
    std::regex colonRegex("::.::.");
    std::regex spectraRegex("spectra");
    std::regex spectrumRegex("spectrum");
    std::regex WEBVTTRegex("WEBVTT");

    while (std::getline(inputFile, line)) {
        // Remove numbers
        line = std::regex_replace(line, numberRegex, "");

        // Remove arrow symbols
        line = std::regex_replace(line, arrowRegex, "");

        // Remove timestamp symbols
        line = std::regex_replace(line, colonRegex, "");

        // Capitalize SPECTRA uses
        line = std::regex_replace(line, spectraRegex, "SPECTRA");
        line = std::regex_replace(line, spectrumRegex, "SPECTRA");

        // Remove the WEBVTT line
        line = std::regex_replace(line, WEBVTTRegex, "");

        if (!line.empty()) {
          outputText += line;
          outputText += '\n';
        }

    }

    // Close the input file
    inputFile.close();

    // Trim leading and trailing whitespace
    outputText = std::regex_replace(outputText, std::regex("^\\s+|\\s+$"), "");

    // Remove duplicates
    outputText = removeDuplicates(outputText);

    // Write the modified text to the output file
    outputFile << outputText;

    // Close the output file
    outputFile.close();

    std::cout << "Output written to output.txt" << std::endl;

    return 0;
}
