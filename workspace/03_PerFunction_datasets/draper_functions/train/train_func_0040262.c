OnServerDataChanged( Packet *packet )
{
	RakNet::BitStream bsIn(packet->data, packet->length, false);
	bsIn.IgnoreBytes(sizeof(MessageID)*2);

	bool objectExists;
	remoteServers.GetIndexFromKey(packet->guid,&objectExists);
	if (objectExists==false)
		return;


	bool wasUpdated=false;
	bsIn.Read(wasUpdated);
	CloudQueryRow row;
	row.Serialize(false, &bsIn, this);

	CloudDataList *cloudDataList;
	bool dataRepositoryExists;
	unsigned int dataRepositoryIndex;
	dataRepositoryIndex = dataRepository.GetIndexFromKey(row.key, &dataRepositoryExists);
	if (dataRepositoryExists==false)
	{
		DeallocateRowData(row.data);
		return;
	}
	cloudDataList = dataRepository[dataRepositoryIndex];
	CloudData *cloudData;
	bool keyDataListExists;
	unsigned int keyDataListIndex = cloudDataList->keyData.GetIndexFromKey(row.clientGUID, &keyDataListExists);
	if (keyDataListExists==true)
	{
		cloudData = cloudDataList->keyData[keyDataListIndex];
		NotifyClientSubscribersOfDataChange(&row, cloudData->specificSubscribers, wasUpdated );
	}

	NotifyClientSubscribersOfDataChange(&row, cloudDataList->nonSpecificSubscribers, wasUpdated );
	DeallocateRowData(row.data);
}
