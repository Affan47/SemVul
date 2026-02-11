str_score(const struct re_str *str) {
    unsigned int score = 0;
    for (int i=0; i < str->len; i++) {
        score += chr_score(str->rx[i]);
    }
    return score;
}
