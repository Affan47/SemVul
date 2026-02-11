Update(RakNet::Time curTime)
{
	if (generatedNonces.Size()>0 && GreaterThan(curTime-5000, generatedNonces[0]->whenGenerated))
	{
		RakNet::OP_DELETE(generatedNonces[0], _FILE_AND_LINE_);
		generatedNonces.RemoveAtIndex(0);
	}
}
