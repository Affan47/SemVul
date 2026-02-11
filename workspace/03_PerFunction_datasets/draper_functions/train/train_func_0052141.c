AddSocket(GSocket *socket, GSocketEvent event)
{
	wxMutexLocker lock(m_lock);
	if (event == GSOCK_INPUT) {
		m_in_set->AddSocket(socket);
	} else {
		m_out_set->AddSocket(socket);
	}
}
