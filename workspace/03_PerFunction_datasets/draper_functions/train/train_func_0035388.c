button_drag_data_get_cb (GtkWidget          *widget,
			 GdkDragContext     *context,
			 GtkSelectionData   *selection_data,
			 guint               info,
			 guint               time_,
			 gpointer            user_data)
{
        ButtonData *button_data;
        char *uri_list[2];
	char *tmp;

	button_data = user_data;

	uri_list[0] = g_file_get_uri (button_data->path);
	uri_list[1] = NULL;

	if (info == NEMO_ICON_DND_GNOME_ICON_LIST) {
		tmp = g_strdup_printf ("%s\r\n", uri_list[0]);
		gtk_selection_data_set (selection_data, gtk_selection_data_get_target (selection_data),
					8, tmp, strlen (tmp));
		g_free (tmp);
	} else if (info == NEMO_ICON_DND_URI_LIST) {
		gtk_selection_data_set_uris (selection_data, uri_list);
	}

	g_free (uri_list[0]);
}
