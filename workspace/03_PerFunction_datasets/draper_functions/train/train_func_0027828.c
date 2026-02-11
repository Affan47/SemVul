xhash(void)
{
    unsigned char *str;
    LVAL len,val;
    int n;


    val = xlgetarg();
    len = xlgafixnum(); n = (int)getfixnum(len);
    xllastarg();


    if (symbolp(val))
        str = getstring(getpname(val));
    else if (stringp(val))
        str = getstring(val);
    else {
        xlerror("bad argument type",val);
        str = NULL;
    }


    return (cvfixnum((FIXTYPE)hash((char *) str, n)));
}
