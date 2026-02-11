rTrim(char *str)
{
    register int p;

    p = strlen(str) - 1;

    while (isspace(str[p]))
    {
        p--;
    }

    str[p + 1] = EOS;

    return str;
}
