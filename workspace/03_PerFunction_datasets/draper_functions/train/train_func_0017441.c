Disconnect()
{
	if( m_connected )
	{
		m_interface.Disconnect();
		SetStatus(_("Ready"));
		m_connected = false;
	}
}
