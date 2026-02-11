add_fd (fd_t fd_, i_poll_events *events_)
{
    poll_entry_t *pe = new poll_entry_t;
    zmq_assert (pe != NULL);


    memset (pe, 0, sizeof (poll_entry_t));

    pe->fd = fd_;
    pe->ev.events = 0;
    pe->ev.data.ptr = pe;
    pe->events = events_;

    int rc = epoll_ctl (epoll_fd, EPOLL_CTL_ADD, fd_, &pe->ev);
    errno_assert (rc != -1);


    load.add (1);

    handle_t handle;
    handle.ptr = pe;
    return handle;
}
