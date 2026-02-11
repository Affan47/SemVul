time2secs(char *tt,struct session *ses)
{
    char *oldtt;
    int w,t=0;

    if (!*tt)
    {
bad:
        tintin_eprintf(ses,"#time format should be: <#y[ears][,] #w #d #h #m [and] #[s]> or just <#> of seconds.");
        tintin_eprintf(ses,"#got: {%s}.",tt);
        return INVALID_TIME;
    };
    t=0;
    for (;;)
    {
        w=strtol(oldtt=tt,&tt,10);
        if (tt==oldtt)
            goto bad;
        while (*tt==' ')
            tt++;
        switch (tolower(*tt))
        {
        case 'w':
            w*=7;
            goto day;
        case 'y':
            w*=365;
        day:
        case 'd':
            w*=24;
        case 'h':
            w*=60;
        case 'm':
            w*=60;
        case 's':
            while (isalpha(*tt))
                tt++;
        case 0:
            t+=w;
            break;
        default:
            goto bad;
        };
        if (*tt==',')
            tt++;
        while (*tt==' ')
            tt++;
        if (!strncmp(tt,"and",3))
            tt+=3;
        if (!*tt)
            break;
    };
    return t;
}
