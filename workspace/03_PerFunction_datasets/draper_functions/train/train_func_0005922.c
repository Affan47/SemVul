sockwant(Socket *s, int rw)
{
    int op;
    struct epoll_event ev = {};

    if (!s->added && !rw) {
        return 0;
    } else if (!s->added && rw) {
        s->added = 1;
        op = EPOLL_CTL_ADD;
    } else if (!rw) {
        op = EPOLL_CTL_DEL;
    } else {
        op = EPOLL_CTL_MOD;
    }

    switch (rw) {
    case 'r':
        ev.events = EPOLLIN;
        break;
    case 'w':
        ev.events = EPOLLOUT;
        break;
    }
    ev.events |= EPOLLRDHUP | EPOLLPRI;
    ev.data.ptr = s;

    return epoll_ctl(epfd, op, s->fd, &ev);
}
