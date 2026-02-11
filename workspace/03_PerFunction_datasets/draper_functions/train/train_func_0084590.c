getnumber(char *cp, long *value)
{
    int             nonum;
    int             isneg;

    if (cp == NULL)
        return NULL;
    nonum = 1;
    isneg = 0;
    *value = 0;
    while (isspace((unsigned char)*cp))
        cp++;
    isneg = (*cp == '-');
    if (isneg)
        cp++;
    while (isdigit((unsigned char)*cp))
    {
        *value = (*value * 10) + *cp++ - '0';
        if (*value < 0)
            return NULL;
        nonum = 0;
    }
    if (isneg)
        *value = -*value;
    if (nonum || (*cp && !isspace((unsigned char)*cp)))
        cp = NULL;
    return cp;
}
