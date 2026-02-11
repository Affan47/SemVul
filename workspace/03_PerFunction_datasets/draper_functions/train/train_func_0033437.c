growEvents(MprWaitService *ws)
{
    ws->eventsMax *= 2;
    if ((ws->events = mprRealloc(ws->events, sizeof(struct epoll_event) * ws->eventsMax)) == 0) {
        mprAssert(!MPR_ERR_MEMORY);
        return MPR_ERR_MEMORY;
    }
    return 0;
}
