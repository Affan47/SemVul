digsequence(nextch,buf,maxlen)
ifun0 nextch;
char *buf;
int maxlen;
{
    int digs = 0;
    int ch = buf[0];

    while(digs < maxlen) {
        if(checkdig(ch)) {
            *buf++ = ch;
            digs++;
            ch = nextch();
        }
        else if(ch == digsep) {
            ch = peekchar(nextch);
            if(checkdig(ch))
                ch = nextch();
            else if(ch == EOL) {
                nextch();
                ch = nextch();
                ch = skipblanks(ch,nextch);
                if(!checkdig(ch))
                    break;
            }
            else
                break;
        }
        else
            break;
    }
    *buf = ch;
    return(digs >= maxlen ? -1 : digs);
}
