Fstk2string()
{
    struct stack *sptr;
    struct stackpage *spage;
    truc currpage;
    truc *ptr;
    char *str, *str1, *str2;
    long llen;
    unsigned len, mlen, slen, pos, k;
    int lineno, pageno;
    int flg;

    if(*FLAGPTR(argStkPtr) != fSTACK) {
        error(stk2arrsym,err_stkv,voidsym);
        return(brkerr());
    }
    sptr = (struct stack *)TAddress(argStkPtr);
    pageno = sptr->pageno;
    lineno = sptr->line;
    llen = pageno;
    llen <<= PAGELENBITS;
    llen += lineno;
    mlen = (getblocksize()-1) & 0xFFFC;
    if(llen > (long)mlen)
        goto errexit;
    len = llen;
    pos = aribufSize*sizeof(word2) & 0xFFFC;
    if(pos/4 > mlen)
        pos = 4*mlen;
    str = (char*)AriBuf;
    str[pos] = '\0';
    currpage = sptr->page;
    spage = (struct stackpage *)Taddress(currpage);
    lineno = (lineno > 0 ? lineno-1 : PAGELEN-1);
    while(len > 0) {
        len--;
        ptr = spage->data + lineno;
        flg = *FLAGPTR(ptr);
        if(flg == fCHARACTER) {
            if(pos > 0) {
                pos--;
                str[pos] = *WORD2PTR(ptr);
            }
            else
                goto errexit;
        }
        else if(flg == fSTRING) {
            str2 = STRINGPTR(ptr);
            slen = *STRLENPTR(ptr);
            if(pos >= slen) {
                pos -= slen;
                for(str1=str+pos, k=0; k<slen; k++)
                    *str1++ = *str2++;
            }
            else
                goto errexit;
        }
        lineno--;
        if(lineno < 0) {
            lineno += PAGELEN;
            if(--pageno < 0)
                break;
            currpage = spage->prevpage;
            spage = (struct stackpage *)Taddress(currpage);
        }
    }
    sptr->line = 0;
    sptr->pageno = 0;
    sptr->page = nullsym;
    return(mkstr(str+pos));
  errexit:
    error(stk2strsym,err_stkbig,voidsym);
    return(brkerr());
}
