notifyAllUserChannels(fmHashTableEntry *pfmHashEntry, UINT16 flags)
{
	if(pfmHashEntry == NULL) return;
	fmChannelListEntry* pEntry = m_pChannelList->getFirstChannelForSocket(pfmHashEntry->pMuxSocket);
	MIXPACKET *notifyPacket = new MIXPACKET;
	memset(notifyPacket, 0, sizeof(MIXPACKET));

	notifyPacket->flags = flags;
	while(pEntry != NULL)
	{
		if(pEntry->bIsSuspended)
		{
			notifyPacket->channel = pEntry->channelOut;
#ifdef _DEBUG
			CAMsg::printMsg(LOG_INFO,"Sent flags %u for channel: %u\n", flags, notifyPacket->channel);
#endif
			m_pQueueSendToMix->add(notifyPacket, sizeof(MIXPACKET));
			pEntry->bIsSuspended = false;
		}
		pEntry=m_pChannelList->getNextChannel(pEntry);
	}
	pfmHashEntry->cSuspend=0;
	delete notifyPacket;
}
