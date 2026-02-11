mprNotifyOn(MprWaitService *ws, MprWaitHandler *wp, int mask)
{
    struct epoll_event  ev;
    int                 fd, rc;

    mprAssert(wp);
    fd = wp->fd;

    lock(ws);
    if (wp->desiredMask != mask) {
        memset(&ev, 0, sizeof(ev));
        ev.data.fd = fd;
        if (wp->desiredMask & MPR_READABLE) {
            ev.events |= (EPOLLIN | EPOLLHUP);
        }
        if (wp->desiredMask & MPR_WRITABLE) {
            ev.events |= EPOLLOUT;
        }
        if (ev.events) {
            rc = epoll_ctl(ws->epoll, EPOLL_CTL_DEL, fd, &ev);
            if (rc != 0) {
                mprError("Epoll del error %d on fd %d\n", errno, fd);
            }
        }
        ev.events = 0;
        if (mask & MPR_READABLE) {
            ev.events |= (EPOLLIN | EPOLLHUP);
        }
        if (mask & MPR_WRITABLE) {
            ev.events |= EPOLLOUT;
        }
        if (ev.events) {
            rc = epoll_ctl(ws->epoll, EPOLL_CTL_ADD, fd, &ev);
            if (rc != 0) {
                mprError("Epoll add error %d on fd %d\n", errno, fd);
            }
        }
        if (mask && fd >= ws->handlerMax) {
            ws->handlerMax = fd + 32;
            if ((ws->handlerMap = mprRealloc(ws->handlerMap, sizeof(MprWaitHandler*) * ws->handlerMax)) == 0) {
                mprAssert(!MPR_ERR_MEMORY);
                return MPR_ERR_MEMORY;
            }
        }
        mprAssert(ws->handlerMap[fd] == 0 || ws->handlerMap[fd] == wp);
        wp->desiredMask = mask;
    }
    ws->handlerMap[fd] = (mask) ? wp : 0;
    unlock(ws);
    return 0;
}
