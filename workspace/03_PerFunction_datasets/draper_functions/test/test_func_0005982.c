reset_colorMap(GtkWidget* entry, gpointer data)
{
	gdouble maxValue = 0;
	gdouble minValue = 0;
	G_CONST_RETURN gchar* tmp;
	ColorMap* colorMap = g_object_get_data(G_OBJECT(entry),"ColorMap");
	ColorMap* newColorMap = NULL;
	GtkWidget* handlebox = g_object_get_data(G_OBJECT(entry), "Handlebox");
	GtkWidget* darea = g_object_get_data(G_OBJECT(entry), "DrawingArea");
	GtkWidget* otherEntry = g_object_get_data(G_OBJECT(entry), "OtherEntry");

	if(!colorMap) return;

	if(colorMap->numberOfColors<1) return;


	if(data)
	{
		minValue = colorMap->colorValue[0].value;
		tmp  = gtk_entry_get_text(GTK_ENTRY(entry));
		maxValue = atof(tmp);
	}
	else
	{
		maxValue = colorMap->colorValue[colorMap->numberOfColors-1].value;
		tmp  = gtk_entry_get_text(GTK_ENTRY(entry));
		minValue = atof(tmp);
	}
	newColorMap = new_colorMap_min_max(minValue, maxValue);
	colormap_free(colorMap);
	g_free(colorMap);

	colorMap = newColorMap;
	g_object_set_data(G_OBJECT(entry),"ColorMap", colorMap);
	g_object_set_data(G_OBJECT(handlebox),"ColorMap", colorMap);
	g_object_set_data(G_OBJECT(darea),"ColorMap", colorMap);
	g_object_set_data(G_OBJECT(otherEntry),"ColorMap", colorMap);


	RebuildSurf = TRUE;
	glarea_rafresh(GLArea);
	color_map_hide(handlebox);
	color_map_refresh(handlebox);
	color_map_show(handlebox);
}
