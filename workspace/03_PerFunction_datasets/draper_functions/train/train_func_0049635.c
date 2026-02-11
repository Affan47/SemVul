OnRNS2Recv(RNS2RecvStruct *recvStruct)
{
	if (incomingDatagramEventHandler)
	{
		if (incomingDatagramEventHandler(recvStruct)!=true)
			return;
	}

	PushBufferedPacket(recvStruct);
	quitAndDataEvents.SetEvent();
}
