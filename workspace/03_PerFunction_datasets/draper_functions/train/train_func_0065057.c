slash_to_backslash(char* p) {
    while (1) {
        char* q = strchr(p, '/');
        if (!q) break;
        *q = '\\';
    }
}
