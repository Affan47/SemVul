glade_app_command_delete (void)
{
	GladeApp           *app;
	GList              *widgets = NULL, *list;
	GladeWidget        *widget;
	gboolean            failed = FALSE;

	app = glade_app_get();
	if (app->priv->active_project == NULL ||
	    glade_project_is_loading (app->priv->active_project))
		return;

	for (list = glade_app_get_selection ();
	     list && list->data; list = list->next)
	{
		widget  = glade_widget_get_from_gobject (list->data);
		widgets = g_list_prepend (widgets, widget);
	}

	if (failed == FALSE && widgets != NULL)
	{
		glade_command_delete (widgets);
		glade_app_update_ui ();
	}
	else if (widgets == NULL)
		glade_util_ui_message (glade_app_get_window(),
				       GLADE_UI_INFO, NULL,
				       _("No widget selected."));

	if (widgets) g_list_free (widgets);
}
