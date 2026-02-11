size(void *, void *device, int width, int height, int raster, unsigned int format, unsigned char *pimage)
{
	if (g_GSInterpreterLib != NULL) {
		return g_GSInterpreterLib->size(device, width, height, raster, format, pimage);
	}
	return 0;
}
