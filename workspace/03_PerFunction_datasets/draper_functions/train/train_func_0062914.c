update_table()
{
	if(rack_area == (GtkWidget *)NULL)
		return;
	GdkRectangle area;
	area.x = area.y = 0;
	area.width = width; area.height = height;
	gtk_widget_draw(GTK_WIDGET(drawing_area), &area);
}
