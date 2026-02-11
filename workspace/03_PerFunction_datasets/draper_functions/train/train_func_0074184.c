ReceiveDescriptor() {
#ifdef SYS_LINUX
	char buf[1];
	struct msghdr m;
	struct iovec iov[1];
	cmsg_fd cm;


	if (ipc_fd_fd < 0)
		return -1;

	iov[0].iov_base = buf;
	iov[0].iov_len = sizeof(buf);

	memset(&m, 0, sizeof(m));

	cm.header.cmsg_len = sizeof(cm);
	m.msg_iov = iov;
	m.msg_iovlen = 1;
	m.msg_control = &cm;
	m.msg_controllen = sizeof(cm);

	if (recvmsg(ipc_fd_fd, &m, 0) < 0) {
		_MSG("Root IPC failed to receive passed file descriptor: " +
			 string(strerror(errno)), MSGFLAG_ERROR);
		return -1;
	}

	return cm.fd;

#endif

	return -1;
}
