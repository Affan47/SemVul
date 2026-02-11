convert_newline(char *line) {
    char *next;
    char buf[MAX_BUF];

    while ((next = strstr(line, "\\n")) != NULL) {
        *next = '\n';
        *(next+1) = '\0';
        snprintf(buf, MAX_BUF, "%s%s", line, next+2);
        strcpy(line, buf);
    }
}
