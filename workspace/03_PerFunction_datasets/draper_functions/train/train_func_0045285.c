prioritycmp(char *a, char *b)
{
    int res;

not_numeric:
    while(*a && *a==*b && !isadigit(*a))
    {
        a++;
        b++;
    }
    if (!a && !b)
        return 0;
    if(!isadigit(*a) || !isadigit(*b))
        return (*a<*b)? -1 : (*a>*b)? 1 : 0;
    while(*a=='0')
        a++;
    while(*b=='0')
        b++;
    res=0;
    while(isadigit(*a))
    {
        if (!isadigit(*b))
            return 1;
        if (*a!=*b && !res)
            res=(*a<*b)? -1 : 1;
        a++;
        b++;
    }
    if (isadigit(*b))
        return -1;
    if (res)
        return res;
    goto not_numeric;
}
