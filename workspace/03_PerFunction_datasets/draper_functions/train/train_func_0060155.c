set_fd_options (long flags_)
{
	trace_with_mask("Socket::set_fd_options",SOCKTRACE);
	int val;
	int ret;

#if defined (WIN32)

	u_long set_nonblock = 1;
	if ((val = ioctlsocket (m_fd, FIONBIO, &set_nonblock)) == 0) {
		m_nonblocking = true;
		return 0;
	}
	return -1;

#else

	if ((val = ::fcntl (m_fd, F_GETFL, 0)) < 0) {
		return -1;
	}
	val |= flags_;

	DL ((SOCKTRACE,"Set flags fcntl(%d, %s)\n", m_fd,
		 decode_fcntl_flags (val).c_str ()));

	ret = ::fcntl (m_fd, F_SETFL, val);

	val = ::fcntl (m_fd, F_GETFL, 0);
	DL ((SOCKTRACE,"Flags are set to %s via fcntl(25)\n",
		 decode_fcntl_flags (val).c_str ()));

	return (ret);

#endif
}
