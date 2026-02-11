Clear(CloudAllocator *allocator)
{
	unsigned int i;
	for (i=0; i < remoteServerResponses.Size(); i++)
	{
		remoteServerResponses[i]->Clear(allocator);
		RakNet::OP_DELETE(remoteServerResponses[i], _FILE_AND_LINE_);
	}
	remoteServerResponses.Clear(false, _FILE_AND_LINE_);
}
