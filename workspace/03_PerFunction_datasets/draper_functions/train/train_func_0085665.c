disconnectSocket(MprSocket *sp)
{
    char    buf[MPR_BUFSIZE];
    int     i, fd;


    if (!mprTryLock(sp->mutex)) {
        return;
    }
    if (sp->fd >= 0 || !(sp->flags & MPR_SOCKET_EOF)) {


        mprLog(6, "Disconnect socket %d", sp->fd);
        mprSetSocketBlockingMode(sp, 0);
        for (i = 0; i < 8; i++) {
            if (recv(sp->fd, buf, sizeof(buf), 0) <= 0) {
                break;
            }
        }
        shutdown(sp->fd, SHUT_RDWR);
        fd = sp->fd;
        sp->flags |= MPR_SOCKET_EOF;
        mprRecallWaitHandlerByFd(fd);
    }
    unlock(sp);
}
