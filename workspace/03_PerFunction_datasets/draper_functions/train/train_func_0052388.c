vd_dnd_get(GtkWidget *widget, GdkDragContext *context,
			   GtkSelectionData *selection_data, guint info,
			   guint time, gpointer data)
{
	ViewDir *vd = data;
	GList *list;
	gchar *uritext = NULL;
	gint length = 0;

	if (!vd->click_fd) return;

	switch (info)
		{
		case TARGET_URI_LIST:
		case TARGET_TEXT_PLAIN:
			list = g_list_prepend(NULL, vd->click_fd);
			uritext = uri_text_from_filelist(list, &length, (info == TARGET_TEXT_PLAIN));
			g_list_free(list);
			break;
		}
	if (uritext)
		{
		gtk_selection_data_set(selection_data, selection_data->target,
				       8, (guchar *)uritext, length);
		g_free(uritext);
		}
}
