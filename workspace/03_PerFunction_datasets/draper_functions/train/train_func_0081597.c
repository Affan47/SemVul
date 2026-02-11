RemoveSpecificSubscriber(RakNetGUID specificSubscriber, CloudDataList *cloudDataList, RakNetGUID remoteCloudClientGuid)
{
	bool keyDataListExists;
	unsigned int keyDataListIndex = cloudDataList->keyData.GetIndexFromKey(specificSubscriber, &keyDataListExists);
	if (keyDataListExists==false)
		return;
	CloudData *cloudData = cloudDataList->keyData[keyDataListIndex];
	bool hasSpecificSubscriber;
	unsigned int specificSubscriberIndex = cloudData->specificSubscribers.GetIndexFromKey(remoteCloudClientGuid, &hasSpecificSubscriber);
	if (hasSpecificSubscriber)
	{
		cloudData->specificSubscribers.RemoveAtIndex(specificSubscriberIndex);
		cloudDataList->subscriberCount--;

		if (cloudData->IsUnused())
		{
			RakNet::OP_DELETE(cloudData, _FILE_AND_LINE_);
			cloudDataList->keyData.RemoveAtIndex(keyDataListIndex);
		}
	}
}
