local_to_utf8(char *d, char *s, int maxb, mbstate_t *cs)
{
    mbstate_t cs0;
    int len,n;
    wchar_t c;

    PROFPUSH("conv: local->utf8");
    if (!cs)
    {
        memset(&cs0, 0, sizeof(cs0));
        cs=&cs0;
    }
    len=strlen(s);
    while(len && maxb>10)
    {
        switch(n=mbrtowc(&c, s, len, cs))
        {
        case -2:
            *d++=BAD_CHAR;
        case 0:
            goto out;
        case -1:
            *d++=BAD_CHAR;
            s++;
            maxb--;
            len--;
            break;
        default:
            s+=n;
            len-=n;
            maxb-=n;
            d+=wc_to_utf8(d, &c, 1, BUFFER_SIZE);
        }
    }
out:
    *d=0;
    PROFPOP;
}
