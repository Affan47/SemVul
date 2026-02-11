lock (const string& fname_)
{
	trace_with_mask ("PidFileLock::lock", PIDFLOCK);

#if defined(WIN32)
	return true;
#else
	int val;
	int len;
	m_filename = Utils::strenv (fname_.c_str ());
	val = len = 0;

	DL((PIDFLOCK,"PID lock file: \"%s\"\n", m_filename.c_str ()));

	if (open_pid_file (m_filename) < 0) {
		goto done;
	}
	DL((PIDFLOCK,"PID lock file opened and locked (fd=%d).\n", m_fd));


	if (ftruncate (m_fd, 0) < 0) {
		log_error("ftruncate() error");
		goto done;
	}
	DL((PIDFLOCK,"PID lock file truncated.\n"));


	if (write_pid () < 0) {
		log_error("write(PID) error");
		goto done;
	}


	if ((val = ::fcntl(m_fd, F_GETFD, 0)) < 0) {
		log_error("fcntl(F_GETFD) error");
		goto done;
	}
	val |= FD_CLOEXEC;

	if (::fcntl (m_fd, F_SETFD, val) < 0) {
		log_error("fcntl(F_SETFD) error");
		goto done;
	}
	DL((PIDFLOCK,"CLOSE-ON-EXEC is set on FD.\n"));

 done:
	if (get_error () != 0) {
		::close (m_fd);
		m_fd = -1;
	}
	return m_error == 0 ? true : false;

#endif
}
