ui_save_buttons_toggle(gboolean enable)
{
	guint i;
	gboolean dirty_tabs = FALSE;

	if (ui_prefs.allow_always_save)
		enable = gtk_notebook_get_n_pages(GTK_NOTEBOOK(main_widgets.notebook)) > 0;

	ui_widget_set_sensitive(widgets.save_buttons[0], enable);
	ui_widget_set_sensitive(widgets.save_buttons[1], enable);


	for (i = 0; i < documents_array->len; i++)
	{


		if (documents[i]->is_valid && documents[i]->changed)
		{
			dirty_tabs = TRUE;
			break;
		}
	}

	ui_widget_set_sensitive(widgets.save_buttons[2], dirty_tabs);
	ui_widget_set_sensitive(widgets.save_buttons[3], dirty_tabs);
}
