blank(char *line)
{
    char *cp = line;

    while (*cp == ' ' || *cp == '\t') cp++;
    return *cp == '\n' || (*cp == '%' && (line[0] != '%' || line[1] != '%'));
}
