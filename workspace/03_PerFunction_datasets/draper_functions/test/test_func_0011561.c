GetMaxOutputWidth(COLORTYPE  rastercolor)
{
	if (rastercolor == COLORTYPE_COLOR)
	{
		if (raster.rasterdata[rastercolor] == NULL)
			return 0;
		else
			return InputWidth*ColorPlaneCount;
	}
	else
	{
		return raster.rastersize[rastercolor];
	}
}
