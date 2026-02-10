IsAvailable(SocketId socket) const
{
	scoped_lock lock(m_mutex);
	SocketQueueMap::const_iterator qi = m_socketQueues.find(socket);
	if( qi == m_socketQueues.end() )
		return false;
	return qi->second->m_queue.size() > 0;
}
