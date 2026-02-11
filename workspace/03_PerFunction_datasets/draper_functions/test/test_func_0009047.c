glade_gtk_color_button_refresh_color (GtkColorButton  *button,
				      GladeWidget     *gbutton)
{
	GladeProperty *property;
	GdkColor       color = { 0, };

	if ((property = glade_widget_get_property (gbutton, "color")) != NULL)
		glade_command_set_property (property, &color);
}
