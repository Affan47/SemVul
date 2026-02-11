b_strerror(int errnum, char *buf, size_t bufsiz)
{
    static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    int stat = 0;
    const char *msg;

    P(mutex);

    msg = strerror(errnum);
    if (!msg) {
       msg = _("Bad errno");
       stat = -1;
    }
    bstrncpy(buf, msg, bufsiz);
    V(mutex);
    return stat;
}
