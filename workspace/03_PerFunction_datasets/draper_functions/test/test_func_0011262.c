PopConnection(unsigned int index, WorldId worldId)
{
	DataStructures::List<Replica3*> replicaList;
	DataStructures::List<NetworkID> destructionList;
	DataStructures::List<Replica3*> broadcastList;
	RakNet::Connection_RM3 *connection;
	unsigned int index2;
	RM3ActionOnPopConnection action;

	RakAssert(worldsArray[worldId]!=0 && "World not in use");
	RM3World *world = worldsArray[worldId];

	connection=world->connectionList[index];


	connection->ClearDownloadGroup(rakPeerInterface);

	RakNetGUID guid = connection->GetRakNetGUID();


	GetReplicasCreatedByGuid(guid, replicaList);

	for (index2=0; index2 < replicaList.Size(); index2++)
	{
		action = replicaList[index2]->QueryActionOnPopConnection(connection);
		replicaList[index2]->OnPoppedConnection(connection);
		if (action==RM3AOPC_DELETE_REPLICA)
		{
			if (replicaList[index2]->GetNetworkIDManager())
				destructionList.Push( replicaList[index2]->GetNetworkID(), _FILE_AND_LINE_  );
		}
		else if (action==RM3AOPC_DELETE_REPLICA_AND_BROADCAST_DESTRUCTION)
		{
			if (replicaList[index2]->GetNetworkIDManager())
				destructionList.Push( replicaList[index2]->GetNetworkID(), _FILE_AND_LINE_  );

			broadcastList.Push( replicaList[index2], _FILE_AND_LINE_  );
		}
		else if (action==RM3AOPC_DO_NOTHING)
		{
			for (unsigned int index3 = 0; index3 < connection->queryToSerializeReplicaList.Size(); index3++)
			{
				LastSerializationResult *lsr = connection->queryToSerializeReplicaList[index3];
				lsr->whenLastSerialized=0;
				if (lsr->lastSerializationResultBS)
				{
					for (int z=0; z < RM3_NUM_OUTPUT_BITSTREAM_CHANNELS; z++)
						lsr->lastSerializationResultBS->bitStream[z].Reset();
				}
			}
		}
	}

	BroadcastDestructionList(broadcastList, connection->GetSystemAddress());
	for (index2=0; index2 < destructionList.Size(); index2++)
	{

		Replica3* replicaToDestroy = world->networkIDManager->GET_OBJECT_FROM_ID<Replica3*>(destructionList[index2]);
		if (replicaToDestroy)
		{
			replicaToDestroy->PreDestruction(connection);
			replicaToDestroy->DeallocReplica(connection);
		}
	}

	world->connectionList.RemoveAtIndex(index);
	return connection;
}
