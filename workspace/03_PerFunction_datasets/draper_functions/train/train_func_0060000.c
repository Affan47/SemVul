padstr(uint8_t *str, const char *src, int len) {
    int i;
    for(i = 0; i < len; i++)
        str[i^1] = *src ? *src++ : ' ';
}
