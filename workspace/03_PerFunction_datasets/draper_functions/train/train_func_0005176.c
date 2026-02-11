setFd (handler_t fd_)
{
	FD_SET (fd_, this);

#if !defined (WIN32)
	ActiveFDs_Iter iter;
	iter = std::find (m_actfds.begin (),
					  m_actfds.end (),
					  fd_);
	if (iter == m_actfds.end ()) {
		m_actfds.push_back (fd_);
	}
#endif

	return true;
}
