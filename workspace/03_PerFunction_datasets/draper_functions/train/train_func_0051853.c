NextOutputRaster(COLORTYPE color)
{
    if (iRastersReady==0)
        return NULL;

	if (myplane == COLORTYPE_BLACK)
	{
		if (raster.rasterdata[myplane] == NULL)
			iRastersReady = 1;
	}
	if (color == COLORTYPE_COLOR)
	{
		iRastersReady--; iRastersDelivered++;
	}
	if (raster.rastersize[color] > 0)
	{
		return pOutputBuffer[color];
	}
	else
	{
		return NULL;
	}
}
