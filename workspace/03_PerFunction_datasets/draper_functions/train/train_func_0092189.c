NextOutputRaster(COLORTYPE color)

{
	if (iRastersReady==0)
		return (BYTE*)NULL;

	if (color == COLORTYPE_BLACK)
	{
		return (BYTE*)NULL;
	}
	else
	{
		iRastersReady=0;
		return compressBuf;
	}
}
