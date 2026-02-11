accumbstr(numptr)
numdata *numptr;
{
    byte *ptr;
    int ch;
    unsigned u, v;
    unsigned len = 0;

    ptr = (byte *)AriBuf;
    while((ch = *numstring++)) {
        u = digval(ch);
        v = digval(*numstring++);
        *ptr++ = (u << 4) + v;
        len++;
    }
    numptr->digits = AriBuf;
    numptr->len = len;
    return(BSTRINGTOK);
}
