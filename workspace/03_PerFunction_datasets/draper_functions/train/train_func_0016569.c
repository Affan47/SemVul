xlib_conn_watch(Display *dpy, void *fds, int fd, int open_flag, void *data)
{
    if (open_flag)
	fdset_add_fd(fds, fd, XProcessInternalConnection, dpy);
    else
	fdset_del_fd(fds, fd);
}
