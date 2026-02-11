glade_gtk_font_button_refresh_font_name (GtkFontButton  *button,
					 GladeWidget    *gbutton)
{
	GladeProperty *property;

	if ((property =
	     glade_widget_get_property (gbutton, "font-name")) != NULL)
		glade_command_set_property  (property,
					     gtk_font_button_get_font_name (button));
}
