ProcessCloudQueryWithAddresses( CloudServer::CloudQueryWithAddresses &cloudQueryWithAddresses, DataStructures::List<CloudData*> &cloudDataResultList, DataStructures::List<CloudKey> &cloudKeyResultList )
{
	CloudQueryResult cloudQueryResult;
	CloudQueryRow cloudQueryRow;
	unsigned int queryIndex;
	bool dataRepositoryExists;
	CloudDataList* cloudDataList;
	unsigned int keyDataIndex;


	for (queryIndex=0; queryIndex < cloudQueryWithAddresses.cloudQuery.keys.Size(); queryIndex++)
	{
		const CloudKey &key = cloudQueryWithAddresses.cloudQuery.keys[queryIndex];

		unsigned int dataRepositoryIndex = dataRepository.GetIndexFromKey(key, &dataRepositoryExists);
		if (dataRepositoryExists)
		{
			cloudDataList=dataRepository[dataRepositoryIndex];

			if (cloudDataList->uploaderCount>0)
			{

				if (cloudQueryWithAddresses.specificSystems.Size()>0)
				{

					unsigned int specificSystemIndex;
					for (specificSystemIndex=0; specificSystemIndex < cloudQueryWithAddresses.specificSystems.Size(); specificSystemIndex++)
					{
						bool uploaderExists;
						keyDataIndex = cloudDataList->keyData.GetIndexFromKey(cloudQueryWithAddresses.specificSystems[specificSystemIndex], &uploaderExists);
						if (uploaderExists)
						{
							cloudDataResultList.Push(cloudDataList->keyData[keyDataIndex], _FILE_AND_LINE_);
							cloudKeyResultList.Push(key, _FILE_AND_LINE_);
						}
					}
				}
				else
				{

					for (keyDataIndex=0; keyDataIndex < cloudDataList->keyData.Size(); keyDataIndex++)
					{
						cloudDataResultList.Push(cloudDataList->keyData[keyDataIndex], _FILE_AND_LINE_);
						cloudKeyResultList.Push(key, _FILE_AND_LINE_);
					}
				}
			}
		}
	}
}
