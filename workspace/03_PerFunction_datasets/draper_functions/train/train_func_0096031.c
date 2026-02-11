strip_line(char *line)
{
    char *p = line + strlen(line);
    while (p > line && (p[-1] == '\n' || p[-1] == '\r'))
        *--p = 0;
}
