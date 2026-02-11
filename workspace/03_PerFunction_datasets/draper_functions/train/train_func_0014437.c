identTimeout(int fd, void *data)
{
    IdentStateData *state = data;
    debug(30, 3) ("identTimeout: FD %d, %s\n", fd,
	inet_ntoa(state->my_peer.sin_addr));
    comm_close(fd);
}
