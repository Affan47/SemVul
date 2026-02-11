CgiRead(Cgi *cgiPtr)
{
    int n;

    cgiPtr->ptr = cgiPtr->buf;
    do {
        n = read(cgiPtr->ofd, cgiPtr->buf, sizeof(cgiPtr->buf));
    } while (n < 0 && errno == EINTR);
    if (n > 0) {
        cgiPtr->cnt = n;
    } else if (n < 0) {
        Ns_Log(Error, "nscgi: pipe read() from %s failed: %s",
                cgiPtr->exec, strerror(errno));
    }
    return n;
}
