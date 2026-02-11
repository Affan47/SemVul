hasMoreRequests()
{
	if (!socket().impl()->initialized()) return false;

	if (_firstRequest)
	{
		_firstRequest = false;
		--_maxKeepAliveRequests;
		return socket().poll(getTimeout(), Socket::SELECT_READ);
	}
	else if (_maxKeepAliveRequests != 0 && getKeepAlive())
	{
		if (_maxKeepAliveRequests > 0)
			--_maxKeepAliveRequests;
		return buffered() > 0 || socket().poll(_keepAliveTimeout, Socket::SELECT_READ);
	}
	else return false;
}
