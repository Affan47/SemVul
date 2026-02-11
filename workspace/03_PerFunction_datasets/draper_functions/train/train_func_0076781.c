addListenPort(const int port)
{
	ListenPort *listenPort = new ListenPort("0.0.0.0", port);
	m_listenPorts.push_back(listenPort);
	if ( !listenPort->isBound() )
		return -1;
	return 0;
}
