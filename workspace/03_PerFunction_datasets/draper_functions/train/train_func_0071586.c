load_wordlist() {
    wordlist_txt.open("wordlist.txt");
    char temp;
    std::size_t k = 0;
    while (wordlist_txt.good()) {
        vector_wordlist.push_back(std::vector <char>());
        wordlist_txt.get(temp);
            while (wordlist_txt.good()) {
                if (temp == '\n') {
                    break;
                }
                vector_wordlist[k].push_back(temp);
                wordlist_txt.get(temp);
            }
        k++;
    }
    std::string temp_s;
    height_wordlist = 0;
    wordlist_txt.clear();
    wordlist_txt.seekg(0);
    while (getline(wordlist_txt, temp_s)) {
        height_wordlist++;
    }
    wordlist_txt.close();
}
