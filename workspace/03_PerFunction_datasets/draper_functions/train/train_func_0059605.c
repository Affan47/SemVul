AutoConstructByQuery(ReplicaManager3 *replicaManager3, WorldId worldId)
{
	ValidateLists(replicaManager3);

	ConstructionMode constructionMode = QueryConstructionMode();

	unsigned int index;
	RM3ConstructionState constructionState;
	LastSerializationResult *lsr;
	index=0;

	constructedReplicasCulled.Clear(false,_FILE_AND_LINE_);
	destroyedReplicasCulled.Clear(false,_FILE_AND_LINE_);

	if (constructionMode==QUERY_REPLICA_FOR_CONSTRUCTION || constructionMode==QUERY_REPLICA_FOR_CONSTRUCTION_AND_DESTRUCTION)
	{
		while (index < queryToConstructReplicaList.Size())
		{
			lsr=queryToConstructReplicaList[index];
			constructionState=lsr->replica->QueryConstruction(this, replicaManager3);
			if (constructionState==RM3CS_ALREADY_EXISTS_REMOTELY || constructionState==RM3CS_ALREADY_EXISTS_REMOTELY_DO_NOT_CONSTRUCT)
			{
				OnReplicaAlreadyExists(index, replicaManager3);
				if (constructionState==RM3CS_ALREADY_EXISTS_REMOTELY)
					constructedReplicasCulled.Push(lsr->replica,_FILE_AND_LINE_);


			}
			else if (constructionState==RM3CS_SEND_CONSTRUCTION)
			{
				OnConstructToThisConnection(index, replicaManager3);
				RakAssert(lsr->replica);
				constructedReplicasCulled.Push(lsr->replica,_FILE_AND_LINE_);
			}
			else if (constructionState==RM3CS_NEVER_CONSTRUCT)
			{
				OnNeverConstruct(index, replicaManager3);
			}
			else
			{

				index++;
			}
		}

		if (constructionMode==QUERY_REPLICA_FOR_CONSTRUCTION_AND_DESTRUCTION)
		{
			RM3DestructionState destructionState;
			index=0;
			while (index < queryToDestructReplicaList.Size())
			{
				lsr=queryToDestructReplicaList[index];
				destructionState=lsr->replica->QueryDestruction(this, replicaManager3);
				if (destructionState==RM3DS_SEND_DESTRUCTION)
				{
					OnSendDestructionFromQuery(index, replicaManager3);
					destroyedReplicasCulled.Push(lsr->replica,_FILE_AND_LINE_);
				}
				else if (destructionState==RM3DS_DO_NOT_QUERY_DESTRUCTION)
				{
					OnDoNotQueryDestruction(index, replicaManager3);
				}
				else
				{

					index++;
				}
			}
		}
	}
	else if (constructionMode==QUERY_CONNECTION_FOR_REPLICA_LIST)
	{
		QueryReplicaList(constructedReplicasCulled,destroyedReplicasCulled);

		unsigned int idx1, idx2;


		for (idx2=0; idx2 < constructedReplicasCulled.Size(); idx2++)
			OnConstructToThisConnection(constructedReplicasCulled[idx2], replicaManager3);

		bool exists;
		for (idx2=0; idx2 < destroyedReplicasCulled.Size(); idx2++)
		{
			exists=false;
			bool objectExists;
			idx1=constructedReplicaList.GetIndexFromKey(destroyedReplicasCulled[idx2], &objectExists);
			if (objectExists)
			{
				constructedReplicaList.RemoveAtIndex(idx1);

				unsigned int j;
				for (j=0; j < queryToSerializeReplicaList.Size(); j++)
				{
					if (queryToSerializeReplicaList[j]->replica==destroyedReplicasCulled[idx2] )
					{
						queryToSerializeReplicaList.RemoveAtIndex(j);
						break;
					}
				}
			}
		}
	}

	SendConstruction(constructedReplicasCulled,destroyedReplicasCulled,replicaManager3->defaultSendParameters,replicaManager3->rakPeerInterface,worldId,replicaManager3);
}
