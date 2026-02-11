rd_str(char *s, char *d) {
    char c;
    bool old = true;

    c = *s++;
    while (c == ' ')
        c = *s++;
    if (c == '"') {
        old = false;
        c = *s++;
    }

    while (c != 0) {
        if (c == '"' && !old) {
            c = *s++;
            break;
        }
        if (c == ' ' && old)
            break;
        if (!old && c == '=') {
            int i = ' ';

            sscanf(s, "%02X", &i);
            s += 2;
            c = (char)(i & 0xFF);
        }
        *d++ = c;
        c = *s++;
    }
    *d = 0;
    return 0;
}
