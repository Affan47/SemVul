unQuote(const char *str)
{
    char *ret, *adp;

    if (!(ret = Malloc(strlen(str) + 1)))
        return 0;
    for (adp = ret; *str; str++, adp++)
        if (*str == '\\')
            switch (*++str) {
            case 0: str--;
            case '\\': *adp = '\\'; break;
            case 'n': *adp = '\n'; break;
            case 't': *adp = '\t'; break;
            default: *adp++ = '\\'; *adp = *str; break;
            }
        else
            *adp = *str;
    *adp = 0;
    return ret;
}
