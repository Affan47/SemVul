Send( const RakNet::BitStream * bitStream, PacketPriority priority, PacketReliability reliability, char orderingChannel, const AddressOrGUID systemIdentifier, bool broadcast, uint32_t forceReceiptNumber )
{
#ifdef _DEBUG
	RakAssert( bitStream->GetNumberOfBytesUsed() > 0 );
#endif

	RakAssert( !( reliability >= NUMBER_OF_RELIABILITIES || reliability < 0 ) );
	RakAssert( !( priority > NUMBER_OF_PRIORITIES || priority < 0 ) );
	RakAssert( !( orderingChannel >= NUMBER_OF_ORDERED_STREAMS ) );

	if ( bitStream->GetNumberOfBytesUsed() == 0 )
		return 0;

	if ( remoteSystemList == 0 || endThreads == true )
		return 0;

	if ( broadcast == false && systemIdentifier.IsUndefined() )
		return 0;

	uint32_t usedSendReceipt;
	if (forceReceiptNumber!=0)
		usedSendReceipt=forceReceiptNumber;
	else
		usedSendReceipt=IncrementNextSendReceipt();

	if (broadcast==false && IsLoopbackAddress(systemIdentifier,true))
	{
		SendLoopback((const char*) bitStream->GetData(),bitStream->GetNumberOfBytesUsed());
		if (reliability>=UNRELIABLE_WITH_ACK_RECEIPT)
		{
			char buff[5];
			buff[0]=ID_SND_RECEIPT_ACKED;
			sendReceiptSerialMutex.Lock();
			memcpy(buff+1, &sendReceiptSerial,4);
			sendReceiptSerialMutex.Unlock();
			SendLoopback( buff, 5 );
		}
		return usedSendReceipt;
	}


	SendBuffered((const char*)bitStream->GetData(), bitStream->GetNumberOfBitsUsed(), priority, reliability, orderingChannel, systemIdentifier, broadcast, RemoteSystemStruct::NO_ACTION, usedSendReceipt);


	return usedSendReceipt;
}
