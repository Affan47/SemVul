ip_addr(int argc, VALUE *argv, VALUE sock)
{
    rb_io_t *fptr;
    struct sockaddr_storage addr;
    socklen_t len = (socklen_t)sizeof addr;
    int norevlookup;

    GetOpenFile(sock, fptr);

    if (argc < 1 || !rsock_revlookup_flag(argv[0], &norevlookup))
	norevlookup = fptr->mode & FMODE_NOREVLOOKUP;
    if (getsockname(fptr->fd, (struct sockaddr*)&addr, &len) < 0)
	rb_sys_fail("getsockname(2)");
    return rsock_ipaddr((struct sockaddr*)&addr, norevlookup);
}
