skip_whitespace(const char *str)
{
    while (*str && isspace(*str))
        str++;
    return str;
}
