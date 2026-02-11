recv(size_t peerId, void * buffer, size_t maxLength)
{
	if(peerId >= maxClients)
	{
		Network::callError(Network::InvalidSlot);
		return -1;
	}

	Peer::Socket & s = sockets[peerId];

	if(s.state == Working)
	{
		return ::recv(s.socket, (char*)buffer, maxLength, 0 );
	}
	size_t dataToProcess = s.bytesRecieved;
	if(maxLength < dataToProcess)
		dataToProcess = maxLength;


	return 0;
}
