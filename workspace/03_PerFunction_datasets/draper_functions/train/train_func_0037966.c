ssh_socket_connect(ssh_socket s, const char *host, int port, const char *bind_addr){
	socket_t fd;

	if(s->state != SSH_SOCKET_NONE) {
		ssh_set_error(s->session, SSH_FATAL,
				"ssh_socket_connect called on socket not unconnected");
		return SSH_ERROR;
	}
	fd=ssh_connect_host_nonblocking(s->session,host,bind_addr,port);
	SSH_LOG(SSH_LOG_PROTOCOL,"Nonblocking connection socket: %d",fd);
	if(fd == SSH_INVALID_SOCKET)
		return SSH_ERROR;
	ssh_socket_set_fd(s,fd);

	return SSH_OK;
}
