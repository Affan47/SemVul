aeGetFileEvents(aeEventLoop *eventLoop, int fd) {
    if (fd >= AE_SETSIZE) return 0;
    aeFileEvent *fe = &eventLoop->events[fd];

    return fe->mask;
}
