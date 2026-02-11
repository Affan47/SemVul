trimWhiteSpace(char *str)
{
    ssize   len;

    if (str == 0) {
        return str;
    }
    while (isspace((int) *str)) {
        str++;
    }
    len = strlen(str) - 1;
    while (isspace((int) str[len])) {
        str[len--] = '\0';
    }
    return str;
}
