split_path( std::string input ) {
    std::vector<std::string> ret;
    std::stringstream ss(input);
    std::string word;
    char delim = ':';
    while ( std::getline( ss, word, delim ) ) {
        ret.push_back(word);
    }
    return ret;
}
