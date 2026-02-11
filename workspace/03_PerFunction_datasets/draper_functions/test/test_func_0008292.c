open_pid_file (const std::string& fname_)
{
	trace_with_mask("PidFileLock::open_pid_file", PIDFLOCK);

#if !defined (WIN32)

	m_fd = ::open (fname_.c_str (), O_WRONLY|O_CREAT, 0644);
	if (m_fd < 0) {
		log_error("open() error.");
		return -1;
	}


	pid_t owner_pid;
	if ((owner_pid = test_region ()) > 0) {
		log_error ("PID file is already locked (by someone).");
		m_error = EPERM;
		return -1;
	}


	if (lock_region () < 0)	{
		if (errno == EACCES || errno == EAGAIN)	{
			log_error("PID file is locked by another process");
		}
		else {
			log_error("write lock error");
		}
		return -1;
	}

#endif

	return 0;
}
