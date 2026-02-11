xlisnumber(char *str, LVAL *pval)
{
    int dl,dr;
    char *p;


    p = str; dl = dr = 0;


    if (*p == '+' || *p == '-')
        p++;


    while (isdigit(*p))
        p++, dl++;


    if (*p == '.') {
        p++;
        while (isdigit(*p))
            p++, dr++;
    }


    if ((dl || dr) && *p == 'E') {
        p++;


        if (*p == '+' || *p == '-')
            p++;


        while (isdigit(*p))
            p++, dr++;
    }


    if ((dl == 0 && dr == 0) || *p)
        return (FALSE);


    if (pval) {
        if (*str == '+') ++str;
        if (str[strlen(str)-1] == '.') str[strlen(str)-1] = 0;
        *pval = (dr ? cvflonum(atof(str)) : cvfixnum(ICNV(str)));
    }
    return (TRUE);
}
