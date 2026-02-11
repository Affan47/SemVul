xdr_skip(XDR* xdrs, unsigned int len)
{
    unsigned int pos;
    if(len <= 0) return 1;
    pos = xdr_getpos(xdrs);
    return xdr_setpos(xdrs,(pos+RNDUP(len)));
}
