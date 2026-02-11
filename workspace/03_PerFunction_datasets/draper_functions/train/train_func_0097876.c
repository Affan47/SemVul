chr_score(char c) {
    if (isalpha(c)) {
        return 2;
    } else if (isalnum(c)) {
        return 3;
    } else if (isprint(c)) {
        return 7;
    } else if (c == '\0') {
        return 10000;
    } else {
        return 100;
    }
}
