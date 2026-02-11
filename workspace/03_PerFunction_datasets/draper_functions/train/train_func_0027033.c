unix_addr(VALUE sock)
{
    rb_io_t *fptr;
    struct sockaddr_un addr;
    socklen_t len = (socklen_t)sizeof addr;

    GetOpenFile(sock, fptr);

    if (getsockname(fptr->fd, (struct sockaddr*)&addr, &len) < 0)
	rb_sys_fail("getsockname(2)");
    return rsock_unixaddr(&addr, len);
}
