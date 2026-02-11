activate_entry_object_image(GtkWidget *entry, gpointer user_data)
{
	G_CONST_RETURN gchar* t;
	GtkWidget* contoursplotplot = NULL;
	GtkWidget* window = NULL;
	ContoursPlotObjectImage* objectImage = NULL;


	if(!GTK_IS_WIDGET(entry)) return;
	if(!user_data || !G_IS_OBJECT(user_data)) return;

	contoursplotplot = GTK_WIDGET(user_data);
	t= gtk_entry_get_text(GTK_ENTRY(entry));
	if(!entry) return;
	window = g_object_get_data(G_OBJECT(entry),"Window");
	objectImage = g_object_get_data(G_OBJECT(entry),"ObjectImage");

	if(!objectImage)
	{
		if(window)gtk_widget_destroy(window);
		return;
	}
	else
	{
		objectImage->widthi =(gint)(fabs(atof(t))*cairo_image_surface_get_width (objectImage->image));
		objectImage->heighti =(gint)(fabs(atof(t))*cairo_image_surface_get_height (objectImage->image));
	}
	if(window)gtk_widget_destroy(window);
	gtk_widget_queue_draw(GTK_WIDGET(contoursplotplot));
}
