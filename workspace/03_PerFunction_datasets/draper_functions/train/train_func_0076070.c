glade_popup_action_add_cb (GtkMenuItem *item, GladeWidget *group)
{
	GladeWidgetAdaptor *adaptor;

	adaptor = glade_palette_get_current_item (glade_app_get_palette ());
	g_return_if_fail (adaptor != NULL);

	glade_command_create (adaptor, group,
			      NULL, glade_widget_get_project (group));

	glade_palette_deselect_current_item (glade_app_get_palette(), TRUE);
}
