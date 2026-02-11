readline(char *line, int line_size, FILE * fp)
{
    if (!fgets(line, line_size, fp)) {
        return -1;
    }
    if (*line && line[strlen(line) - 1] == '\n') {
        line[strlen(line) - 1] = '\0';
    }
    if (*line && line[strlen(line) - 1] == '\r') {
        line[strlen(line) - 1] = '\0';
    }
    return 0;
}
