shortenString(char *s)
{
    char *end = strchr(s, '\0');

    while (end>s && isspace(end[-1])) {
        *--end = 0;
    }
    while (isspace(s[0])) {
        s++;
    }

    return s;
}
