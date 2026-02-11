printbstring(strom,obj,fptr)
truc strom,obj;
forminfo *fptr;
{
    struct strcell *strpt;
    byte *buf;
    size_t k = 0, len;
    int n = 0, m, grp;
    int weiter = 1;

    strpt = stringptr(obj);
    buf = (byte *)&(strpt->ch0);
    len = strpt->len;
    grp = fptr->param[2];
    if(grp == 1)
        grp = 2;
    else if(grp > PrintCols-1)
        grp = PrintCols-1;
    if(quotemode)
        n = strcopy(OutBuf,"$");
    while(weiter) {
        m = (grp ? grp/2 : 2);
        if(k+m > len)
            m = (k <= len ? len-k : 0);
        n += bytes2hex(OutBuf+n,buf+k,m);
        if(k+m < len) {
            if(grp)
                n += strcopy(OutBuf+n,"_");
            k += m;
        }
        else
            weiter = 0;
        fprintmarg(strom,OutBuf,n);
        n = 0;
    }
}
