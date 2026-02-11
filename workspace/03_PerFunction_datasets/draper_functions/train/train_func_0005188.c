xconnect(int s, const struct sockaddr *s_addr, socklen_t addrlen)
{
	if (connect(s, s_addr, addrlen) < 0) {
		if (ENABLE_FEATURE_CLEAN_UP)
			close(s);
		if (s_addr->sa_family == AF_INET)
			bb_perror_msg_and_die("%s (%s)",
				"can't connect to remote host",
				inet_ntoa(((struct sockaddr_in *)s_addr)->sin_addr));
		bb_perror_msg_and_die("can't connect to remote host");
	}
}
