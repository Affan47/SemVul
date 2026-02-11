closeSocket(MprSocket *sp, bool gracefully)
{
    MprSocketService    *ss;
    MprTime             timesUp;
    char                buf[16];

    ss = MPR->socketService;

    lock(sp);
    if (sp->flags & MPR_SOCKET_CLOSED) {
        unlock(sp);
        return;
    }
    sp->flags |= MPR_SOCKET_CLOSED | MPR_SOCKET_EOF;

    if (sp->fd >= 0) {


        mprLog(6, "Close socket %d, graceful %d", sp->fd, gracefully);
        if (gracefully) {
            mprSetSocketBlockingMode(sp, 0);
            while (recv(sp->fd, buf, sizeof(buf), 0) > 0) {
                ;
            }
        }
        if (shutdown(sp->fd, SHUT_RDWR) == 0) {
            if (gracefully) {
                timesUp = mprGetTime() + MPR_TIMEOUT_LINGER;
                do {
                    if (recv(sp->fd, buf, sizeof(buf), 0) <= 0) {
                        break;
                    }
                } while (mprGetTime() < timesUp);
            }
        }
        closesocket(sp->fd);
        sp->fd = -1;
    }

    if (! (sp->flags & (MPR_SOCKET_LISTENER | MPR_SOCKET_CLIENT))) {
        mprLock(ss->mutex);
        if (--ss->numAccept < 0) {
            ss->numAccept = 0;
        }
        mprUnlock(ss->mutex);
    }
    unlock(sp);
}
