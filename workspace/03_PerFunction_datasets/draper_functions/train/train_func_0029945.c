rm_fd (handle_t handle_)
{

    fd_t fd = handle_.fd;


    fd_set_t::iterator it;
    for (it = fds.begin (); it != fds.end (); it ++)
        if (it->fd == fd)
            break;
    zmq_assert (it != fds.end ());
    it->fd = retired_fd;
    retired = true;


    FD_CLR (fd, &source_set_in);
    FD_CLR (fd, &source_set_out);
    FD_CLR (fd, &source_set_err);


    FD_CLR (fd, &readfds);
    FD_CLR (fd, &writefds);
    FD_CLR (fd, &exceptfds);


    if (fd == maxfd) {
        maxfd = retired_fd;
        for (fd_set_t::iterator it = fds.begin (); it != fds.end (); it ++)
            if (it->fd > maxfd)
                maxfd = it->fd;
    }


    load.sub (1);
}
