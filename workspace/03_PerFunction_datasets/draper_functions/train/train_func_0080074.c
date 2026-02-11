NotifyClientSubscribersOfDataChange( CloudQueryRow *row, DataStructures::OrderedList<RakNetGUID, RakNetGUID> &subscribers, bool wasUpdated )
{
	RakNet::BitStream bsOut;
	bsOut.Write((MessageID) ID_CLOUD_SUBSCRIPTION_NOTIFICATION);
	bsOut.Write(wasUpdated);
	row->Serialize(true,&bsOut,0);

	unsigned int i;
	for (i=0; i < subscribers.Size(); i++)
	{
		SendUnified(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, subscribers[i], false);
	}
}
