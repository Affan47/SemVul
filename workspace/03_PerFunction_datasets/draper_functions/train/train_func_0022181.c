gw_accept(int fd, Octstr **client_addr)
{
    struct sockaddr_in addr;
    socklen_t addrlen;
    int new_fd;

    if (gwthread_pollfd(fd, POLLIN, -1.0) != POLLIN) {
	debug("gwlib.socket", 0, "gwthread_pollfd interrupted or failed");
	return -1;
    }
    addrlen = sizeof(addr);
    new_fd = accept(fd, (struct sockaddr *) &addr, &addrlen);
    if (new_fd == -1) {
	error(errno, "accept system call failed.");
	return -1;
    }
    *client_addr = host_ip(addr);
    debug("test_smsc", 0, "accept() succeeded, client from %s",
	  octstr_get_cstr(*client_addr));
    return new_fd;
}
