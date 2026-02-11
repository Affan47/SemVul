on_disconnect_all()
{
	for( unsigned int i = 0; i < m_device_count; ++i )
		Disconnect(m_threads[i].get());
}
