ClearByAddress(RakNet::AddressOrGUID remoteSystem)
{
	unsigned int i=0;
	while (i < generatedNonces.Size())
	{
		if (generatedNonces[i]->remoteSystem==remoteSystem)
		{
			RakNet::OP_DELETE(generatedNonces[i],_FILE_AND_LINE_);
			generatedNonces.RemoveAtIndex(i);
		}
		else
		{
			i++;
		}
	}
}
