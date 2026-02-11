PushConnection(RakNet::Connection_RM3 *newConnection, WorldId worldId)
{
	if (newConnection==0)
		return false;
	if (GetConnectionByGUID(newConnection->GetRakNetGUID(), worldId))
		return false;

	RakAssert(newConnection->GetRakNetGUID()!=rakPeerInterface->GetMyGUID());

	RakAssert(worldsArray[worldId]!=0 && "World not in use");
	RM3World *world = worldsArray[worldId];

	unsigned int index = world->connectionList.GetIndexOf(newConnection);
	if (index==(unsigned int)-1)
	{
		world->connectionList.Push(newConnection,_FILE_AND_LINE_);


		newConnection->SendValidation(rakPeerInterface, worldId);

		Connection_RM3::ConstructionMode constructionMode = newConnection->QueryConstructionMode();
		if (constructionMode==Connection_RM3::QUERY_REPLICA_FOR_CONSTRUCTION || constructionMode==Connection_RM3::QUERY_REPLICA_FOR_CONSTRUCTION_AND_DESTRUCTION)
		{
			unsigned int pushIdx;
			for (pushIdx=0; pushIdx < world->userReplicaList.Size(); pushIdx++)
				newConnection->OnLocalReference(world->userReplicaList[pushIdx], this);
		}
	}
	return true;
}
