EncodeString( const char *input, int maxCharsToWrite, RakNet::BitStream *output )
{
	unsigned index;
	bool objectExists;

	index=orderedStringList.GetIndexFromKey((char*)input, &objectExists);
	if (objectExists)
	{
		output->Write(true);
		output->Write((StringTableType)index);
	}
	else
	{
		LogStringNotFound(input);
		output->Write(false);
		StringCompressor::Instance()->EncodeString(input, maxCharsToWrite, output);
	}
}
