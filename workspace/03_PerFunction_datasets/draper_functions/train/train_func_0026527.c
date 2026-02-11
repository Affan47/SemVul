RemoveWorld(WorldId worldId)
{
	RakAssert(worldsArray[worldId]!=0 && "World not in use");
	for (unsigned int i=0; i < worldsList.Size(); i++)
	{
		if (worldsList[i]==worldsArray[worldId])
		{
			RakNet::OP_DELETE(worldsList[i],_FILE_AND_LINE_);
			worldsList.RemoveAtIndexFast(i);
			break;
		}
	}
	worldsArray[worldId]=0;

}
