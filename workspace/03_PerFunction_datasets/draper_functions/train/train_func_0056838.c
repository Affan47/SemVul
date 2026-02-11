inputout(str,putfun)
byte *str;
ifun putfun;
{
    int ch, k;

    ch = *str++;
    while(ch) {
        if(ch < TABESC-1)
            k = ch - 1;
        else if(ch == TABESC)
            k = *str++;
        else
            k = 0;
        while(--k >= 0)
            putfun(' ');
        while((ch = *str++) > TABESC)
            putfun(ch);
        putfun('\n');
    }
}
