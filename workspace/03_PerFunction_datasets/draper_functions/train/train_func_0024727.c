new_colorMap_min_max_unicolor(gdouble minValue, gdouble maxValue, gdouble Color[])
{
	gdouble color[3];
	ColorMap* colorMap;

	gdouble max = color[0];
	gint c;

	for(c=0;c<3;c++) color[c] = Color[c];
	max = color[0];
	if(max<color[1]) max = color[1];
	if(max<color[2]) max = color[2];
	if(max<1e-3)
	{
		color[0] = 1.0;
		color[1] = 1.0;
		color[2] = 1.0;
		max = 1.0;
	}

	for(c=0;c<3;c++) color[c] /= max;
	colorMap = g_malloc(sizeof(ColorMap));
	*colorMap = new_colorMap(color, minValue);
	color[0] = 0; color[1] = 0; color[2] = 0;
	add_to_colorMap(colorMap, color, maxValue );
	sort_colorMap(colorMap);
	return colorMap;
}
