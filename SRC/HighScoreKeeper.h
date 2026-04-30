#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

// Holds one entry in the high score table
struct HighScoreEntry {
    std::string name;
    int score;
};

class HighScoreKeeper
{
public:
    // Load all scores from file, returns them as a vector
    static std::vector<HighScoreEntry> LoadScores(const std::string& filename = "highscores.txt")
    {
        std::vector<HighScoreEntry> scores;
        std::ifstream file(filename);
        HighScoreEntry entry;
        while (file >> entry.name >> entry.score)
        {
            scores.push_back(entry);
        }
        file.close();
        return scores;
    }

    // Save a new name+score, sort highest first, keep top 10, write back to file
    static void SaveScore(const std::string& name, int score, const std::string& filename = "highscores.txt")
    {
        auto scores = LoadScores(filename);
        scores.push_back({ name, score });
        std::sort(scores.begin(), scores.end(), [](auto& a, auto& b) {
            return a.score > b.score;
            });
        if (scores.size() > 10) scores.resize(10);

        std::ofstream file(filename);
        for (auto& s : scores)
        {
            file << s.name << " " << s.score << "\n";
        }
        file.close();
    }
};