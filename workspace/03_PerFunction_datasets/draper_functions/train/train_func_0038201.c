glade_palette_create_root_widget (GladePalette *palette, GladeWidgetAdaptor *adaptor)
{
	GladeWidget *widget;


	if ((widget = glade_command_create (adaptor, NULL, NULL, glade_app_get_project ())) != NULL)
		glade_palette_deselect_current_item (palette, FALSE);

	return widget;
}
