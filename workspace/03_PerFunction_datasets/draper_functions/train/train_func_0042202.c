clientGetPinnedInfo(const ConnStateData * conn, const request_t * request, peer ** peer)
{
    int fd = conn->pinning.fd;

    if (fd < 0)
	return -1;

    if (conn->pinning.auth && request && strcasecmp(conn->pinning.host, request->host) != 0) {
      err:
	comm_close(fd);
	return -1;
    }
    if (request && conn->pinning.port != request->port)
	goto err;
    if (conn->pinning.peer && !cbdataValid(conn->pinning.peer))
	goto err;
    *peer = conn->pinning.peer;
    return fd;
}
