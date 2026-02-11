nextLine(const char* buffer)
{
	int numBytesRead=0;

	while (*buffer != '\n')
	{
		buffer++;
		numBytesRead++;
	}


	if (buffer[0]==0x0a)
	{
		buffer++;
		numBytesRead++;
	}
	return numBytesRead;
}
