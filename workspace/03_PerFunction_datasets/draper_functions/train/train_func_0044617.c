mem_setbytes(JSXDRState *xdr, char *bytes, uint32 len)
{
    MEM_NEED(xdr, len);
    memcpy(MEM_DATA(xdr), bytes, len);
    MEM_INCR(xdr, len);
    return JS_TRUE;
}
