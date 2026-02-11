make_path_from_file(char *s, char *t) {
    char *pos = "";
    char *c;

    for (c = t + strlen(t); c != s; c--)
        if (*c == '/') {
            pos = c;
            break;
        }

    if (c == t) {
        return (-1);
    }

    strncpy(s, t, pos - t);
    return 1;
}
