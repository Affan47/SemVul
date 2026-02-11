find_option(char c) {
    map<char,int>::iterator o = char_to_option.find(c);
    if (o == char_to_option.end()) return NULL;
    else return &(options[o->second]);
}
