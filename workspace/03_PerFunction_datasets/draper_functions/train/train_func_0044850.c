mprCreateNotifierService(MprWaitService *ws)
{
    struct epoll_event  ev;

    ws->eventsMax = MPR_EPOLL_SIZE;
    ws->handlerMax = MPR_FD_MIN;
    ws->events = mprAllocZeroed(sizeof(struct epoll_event) * ws->eventsMax);
    ws->handlerMap = mprAllocZeroed(sizeof(MprWaitHandler*) * ws->handlerMax);
    if (ws->events == 0 || ws->handlerMap == 0) {
        return MPR_ERR_CANT_INITIALIZE;
    }
    if ((ws->epoll = epoll_create(MPR_EPOLL_SIZE)) < 0) {
        mprError("Call to epoll() failed");
        return MPR_ERR_CANT_INITIALIZE;
    }


    if (pipe(ws->breakPipe) < 0) {
        mprError("Can't open breakout pipe");
        return MPR_ERR_CANT_INITIALIZE;
    }
    fcntl(ws->breakPipe[0], F_SETFL, fcntl(ws->breakPipe[0], F_GETFL) | O_NONBLOCK);
    fcntl(ws->breakPipe[1], F_SETFL, fcntl(ws->breakPipe[1], F_GETFL) | O_NONBLOCK);

    memset(&ev, 0, sizeof(ev));
    ev.events = EPOLLIN | EPOLLERR | EPOLLHUP;
    ev.data.fd = ws->breakPipe[MPR_READ_PIPE];
    epoll_ctl(ws->epoll, EPOLL_CTL_ADD, ws->breakPipe[MPR_READ_PIPE], &ev);
    return 0;
}
