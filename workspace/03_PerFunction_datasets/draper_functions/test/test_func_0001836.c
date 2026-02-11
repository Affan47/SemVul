showColorMapContours()
{
	GtkWidget* handleBoxColorMapContours = g_object_get_data(G_OBJECT(PrincipalWindow), "HandleboxColorMapContours");
	ColorMap* colorMap = g_object_get_data(G_OBJECT( handleBoxColorMapContours),"ColorMap");
	if(!colorMap) setColorMap();

	color_map_show(handleBoxColorMapContours);
}
