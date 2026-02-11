SetBufferSizes(int size_read, int size_write)
{
	if (m_pSocketThread)
		m_pSocketThread->m_sync.Lock();

	m_buffer_sizes[0] = size_read;
	m_buffer_sizes[1] = size_write;

	if (m_fd != -1)
		DoSetBufferSizes(m_fd, size_read, size_write);

	if (m_pSocketThread)
		m_pSocketThread->m_sync.Unlock();
}
