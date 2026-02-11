ajSysCommandCopyC(const char* name, const char* name2)
{
    int from;
    int to;
    int n;
    int nw;
    char cbuf[1024];
    char *buf;

    from = open(name, O_RDONLY);
    if(from < 0)
    {
        ajErr("Unable to copy '%s' error %d: %s",
              name, errno, strerror(errno));
        return ajFalse;
    }

    to = open(name2, O_WRONLY|O_CREAT, 0644);
    if(to < 0)
    {
        ajErr("Unable to copy to '%s' error %d: %s",
              name2, errno, strerror(errno));
        return ajFalse;
    }

    while((n = read(from, cbuf, sizeof(cbuf))) > 0)
    {
        buf = cbuf;
        do
        {
            nw = write(to, buf, n);
            if(nw == n)
                break;
            if(nw > 0)
            {
                buf += nw;
                n -= nw;
            }
        } while (nw >= 0 || errno == EINTR);
        if(nw < 0)
        {
            ajErr("Write to %s failed, error:%d %s",
                  name2, errno, strerror(errno));
            return ajFalse;
        }
    }

    close(from);
    close(to);

    return ajTrue;
}
