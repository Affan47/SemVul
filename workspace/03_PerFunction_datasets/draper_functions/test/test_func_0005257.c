close()
{
	if (_isOpen)
	{
		try
		{
			endTransfer();
		}
		catch (...)
		{
		}
		std::string response;
		sendCommand("QUIT", response);
		_controlSocket.close();
		_isOpen = false;
	}
}
