httpSetHeader(HttpConn *conn, cchar *key, cchar *fmt, ...)
{
    char        *value;
    va_list     vargs;

    mprAssert(key && *key);
    mprAssert(fmt && *fmt);

    va_start(vargs, fmt);
    value = sfmtv(fmt, vargs);
    va_end(vargs);
    addHdr(conn, key, value);
}
