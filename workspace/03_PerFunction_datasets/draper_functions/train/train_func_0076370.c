appendErrMessage(const MockHTTP *mh, const char *fmt, ...)
{
    apr_pool_t *scratchpool;
    apr_size_t startpos = strlen(mh->errmsg);
    apr_size_t len;
    const char *msg;
    va_list argp;

    apr_pool_create(&scratchpool, mh->pool);
    msg = apr_pvsprintf(scratchpool, fmt, argp);

    len = strlen(msg) + 1;
    len = startpos + len > ERRMSG_MAXSIZE ? ERRMSG_MAXSIZE - startpos - 1: len;
    memcpy(mh->errmsg + startpos, msg, len);

    apr_pool_destroy(scratchpool);
}
