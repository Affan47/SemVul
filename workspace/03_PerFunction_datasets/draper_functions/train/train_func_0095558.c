RequestForwarding(SystemAddress proxyCoordinator, SystemAddress sourceAddress, SystemAddress targetAddressAsSeenFromCoordinator, RakNet::TimeMS timeoutOnNoDataMS, RakNet::BitStream *serverSelectionBitstream)
{

	ConnectionState cs = rakPeerInterface->GetConnectionState(proxyCoordinator);
	if (cs!=IS_CONNECTED)
		return false;


	RakAssert(resultHandler!=0);
	if (resultHandler==0)
		return false;

	BitStream outgoingBs;
	outgoingBs.Write((MessageID)ID_UDP_PROXY_GENERAL);
	outgoingBs.Write((MessageID)ID_UDP_PROXY_FORWARDING_REQUEST_FROM_CLIENT_TO_COORDINATOR);
	outgoingBs.Write(sourceAddress);
	outgoingBs.Write(true);
	outgoingBs.Write(targetAddressAsSeenFromCoordinator);
	outgoingBs.Write(timeoutOnNoDataMS);
	if (serverSelectionBitstream && serverSelectionBitstream->GetNumberOfBitsUsed()>0)
	{
		outgoingBs.Write(true);
		outgoingBs.Write(serverSelectionBitstream);
	}
	else
	{
		outgoingBs.Write(false);
	}
	rakPeerInterface->Send(&outgoingBs, MEDIUM_PRIORITY, RELIABLE_ORDERED, 0, proxyCoordinator, false);

	return true;
}
