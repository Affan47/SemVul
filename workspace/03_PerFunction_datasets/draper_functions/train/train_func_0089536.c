sendPortCommand(const SocketAddress& addr)
{
	if (_supports1738)
	{
		if (sendEPRT(addr))
			return;
		else
			_supports1738 = false;
	}
	sendPORT(addr);
}
