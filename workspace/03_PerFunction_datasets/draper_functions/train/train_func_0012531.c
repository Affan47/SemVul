read_window_override_int(const char* s, int* pos, int* out) {
    char temp[4];
    int read = 0;
    while(s[*pos] == ' ') ++(*pos);
    while (read < 3) {
        temp[read] = s[*pos];
        ++(*pos);
        ++read;
        char c= s[*pos];
        if (c >= '0' && c <= '9') {
            continue;
        }
        temp[read] = '\0';
        if (read == 1) {
            if (temp[0] == '*') {
                *out = -1;
                return 1;
            }
        }
        *out = atoi(temp);
        return 1;
    }

    return 0;
}
