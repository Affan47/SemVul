WaitAll(PollEvent* ve, size_t max) const
{
    PollEvent event;

    struct epoll_event ev[max];
    int n = epoll_wait(epoll_, ev, max, -1);

    for (int i = 0; i < n; ++i)
    {
        unsigned flag = ev[i].events;
        event.data  = ev[i].data.ptr;
        event.write = ((flag & EPOLLOUT) != 0);
        event.read  = ((flag & EPOLLIN) != 0);

        ve[i] = event;
    }

    return n;
}
