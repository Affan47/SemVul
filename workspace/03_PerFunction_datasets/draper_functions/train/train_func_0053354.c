BeginningOfWord (int index) {
    const char* t = Text(index);
    while (t > text && !(!isalnum(*(t-1)) && isalnum(*t))) {
        --t;
    }
    return t - text;
}
