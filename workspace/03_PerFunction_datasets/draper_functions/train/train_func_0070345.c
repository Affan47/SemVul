OnReleaseRequest(Packet *packet)
{
	RakNet::BitStream bsIn(packet->data, packet->length, false);
	bsIn.IgnoreBytes(sizeof(MessageID));

	uint16_t keyCount;
	bsIn.Read(keyCount);

	if (keyCount==0)
		return;

	DataStructures::HashIndex remoteSystemIndex = remoteSystems.GetIndexOf(packet->guid);
	if (remoteSystemIndex.IsInvalid()==true)
		return;

	RemoteCloudClient* remoteCloudClient = remoteSystems.ItemAtIndex(remoteSystemIndex);

	CloudKey key;


	DataStructures::List<CloudKey> cloudKeys;
	for (uint16_t keyCountIndex=0; keyCountIndex < keyCount; keyCountIndex++)
	{
		key.Serialize(false, &bsIn);
		cloudKeys.Push(key, _FILE_AND_LINE_);
	}

	for (unsigned int filterIndex=0; filterIndex < queryFilters.Size(); filterIndex++)
	{
		if (queryFilters[filterIndex]->OnReleaseRequest(packet->guid, packet->systemAddress, cloudKeys)==false)
			return;
	}

	for (uint16_t keyCountIndex=0; keyCountIndex < keyCount; keyCountIndex++)
	{


		key=cloudKeys[keyCountIndex];


		bool objectExists;
		unsigned int uploadedKeysIndex = remoteCloudClient->uploadedKeys.GetIndexFromKey(key,&objectExists);
		if (objectExists)
		{
			bool dataRepositoryExists;
			unsigned int dataRepositoryIndex = dataRepository.GetIndexFromKey(key, &dataRepositoryExists);
			CloudDataList* cloudDataList = dataRepository[dataRepositoryIndex];
			RakAssert(cloudDataList);

			CloudData *cloudData;
			bool keyDataListExists;
			unsigned int keyDataListIndex = cloudDataList->keyData.GetIndexFromKey(packet->guid, &keyDataListExists);
			cloudData = cloudDataList->keyData[keyDataListIndex];

			remoteCloudClient->uploadedKeys.RemoveAtIndex(uploadedKeysIndex);
			remoteCloudClient->uploadedBytes-=cloudData->dataLengthBytes;
			cloudDataList->uploaderCount--;


			NotifyClientSubscribersOfDataChange(cloudData, cloudDataList->key, cloudData->specificSubscribers, false );
			NotifyClientSubscribersOfDataChange(cloudData, cloudDataList->key, cloudDataList->nonSpecificSubscribers, false );
			NotifyServerSubscribersOfDataChange(cloudData, cloudDataList->key, false );

			cloudData->Clear();

			if (cloudData->IsUnused())
			{
				RakNet::OP_DELETE(cloudData, _FILE_AND_LINE_);
				cloudDataList->keyData.RemoveAtIndex(keyDataListIndex);
				if (cloudDataList->IsNotUploaded())
				{

					RemoveUploadedKeyFromServers(cloudDataList->key);
				}

				if (cloudDataList->IsUnused())
				{
					RakNet::OP_DELETE(cloudDataList, _FILE_AND_LINE_);
					dataRepository.RemoveAtIndex(dataRepositoryIndex);
				}
			}

			if (remoteCloudClient->IsUnused())
			{
				RakNet::OP_DELETE(remoteCloudClient, _FILE_AND_LINE_);
				remoteSystems.RemoveAtIndex(remoteSystemIndex, _FILE_AND_LINE_);
				break;
			}
		}
	}
}
