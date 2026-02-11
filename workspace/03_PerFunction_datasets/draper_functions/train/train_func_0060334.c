colormap_free(ColorMap* colorMap)
{
	if(!colorMap) return;
	if(!colorMap->colorValue)
	{

		colorMap->numberOfColors = 0;
		return;
	}
	g_free(colorMap->colorValue);
	colorMap->numberOfColors = 0;
}
