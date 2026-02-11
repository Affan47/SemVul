histinp(nextch,buf)
ifun0 nextch;
char *buf;
{
    int ch;

    *buf++ = '!';
    ch = nextch();
    if(ch == '!') {
        *buf++ = '!';
        if(nextch() == '!') {
            *buf++ = '!';
            ch = nextch();
        }
    }
    else if(ch >= 'a' && ch <= 'c') {
        *buf++ = ch;
        ch = nextch();
    }
    if(ch == '.')
        nextch();
    *buf = 0;
    return(HISTORYTOK);
}
