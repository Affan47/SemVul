OnForwardingSuccess(Packet *packet)
{
	RakNet::BitStream bs(packet->data, packet->length, false);
	bs.IgnoreBytes(sizeof(MessageID));
	RakNetGUID endpointGuid;
	bs.Read(endpointGuid);
	unsigned short sourceToDestPort;
	bs.Read(sourceToDestPort);

	unsigned int forwardingIndex;
	forwardedConnectionListMutex.Lock();
	for (forwardingIndex=0; forwardingIndex < forwardedConnectionList.Size(); forwardingIndex++)
	{
		if (forwardedConnectionList[forwardingIndex].endpointGuid==endpointGuid)
			break;
	}

	if (forwardingIndex<forwardedConnectionList.Size())
	{

		SystemAddress intermediaryAddress=packet->systemAddress;
		intermediaryAddress.SetPortHostOrder(sourceToDestPort);
		rakPeerInterface->ChangeSystemAddress(endpointGuid, intermediaryAddress);


        ForwardedConnection& ref_fc     = forwardedConnectionList[forwardingIndex];
    	ref_fc.intermediaryAddress      = packet->systemAddress;
		ref_fc.intermediaryAddress.SetPortHostOrder(sourceToDestPort);
		ref_fc.intermediaryGuid         = packet->guid;


		if (debugInterface)
		{
			char buff[512];
			debugInterface->ShowDiagnostic(FormatStringTS(buff,"Got ID_ROUTER_2_FORWARDING_ESTABLISHED, returning ID_ROUTER_2_REROUTED, Calling RakPeer::ChangeSystemAddress at %s:%i\n", _FILE_AND_LINE_));
		}

		packet->data[0]=ID_ROUTER_2_REROUTED;

    	forwardedConnectionListMutex.Unlock();
		return true;
	}
	else
	{
		forwardedConnectionListMutex.Unlock();


		ForwardedConnection fc;
		connectionRequestsMutex.Lock();
		unsigned int connectionRequestIndex = GetConnectionRequestIndex(endpointGuid);
		fc.returnConnectionLostOnFailure=connectionRequests[connectionRequestIndex]->returnConnectionLostOnFailure;
		connectionRequests.RemoveAtIndexFast(connectionRequestIndex);
		connectionRequestsMutex.Unlock();
		fc.endpointGuid=endpointGuid;
		fc.intermediaryAddress=packet->systemAddress;
		fc.intermediaryAddress.SetPortHostOrder(sourceToDestPort);
		fc.intermediaryGuid=packet->guid;
		fc.weInitiatedForwarding=true;


		forwardedConnectionListMutex.Lock();
		forwardedConnectionList.Push (fc,_FILE_AND_LINE_);
		forwardedConnectionListMutex.Unlock();

		if (debugInterface)
		{
			char buff[512];
			debugInterface->ShowDiagnostic(FormatStringTS(buff,"Got and returning to user ID_ROUTER_2_FORWARDING_ESTABLISHED at %s:%i\n", _FILE_AND_LINE_));
		}

	}
	return true;
}
