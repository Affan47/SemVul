collection_table_dnd_get(GtkWidget *widget, GdkDragContext *context,
				     GtkSelectionData *selection_data, guint info,
				     guint time, gpointer data)
{
	CollectTable *ct = data;
	gboolean selected;
	GList *list = NULL;
	gchar *uri_text = NULL;
	gint total;

	if (!ct->click_info) return;

	selected = INFO_SELECTED(ct->click_info);

	switch (info)
		{
		case TARGET_APP_COLLECTION_MEMBER:
			if (selected)
				{
				uri_text = collection_info_list_to_dnd_data(ct->cd, ct->selection, &total);
				}
			else
				{
				list = g_list_append(NULL, ct->click_info);
				uri_text = collection_info_list_to_dnd_data(ct->cd, list, &total);
				g_list_free(list);
				}
			break;
		case TARGET_URI_LIST:
		case TARGET_TEXT_PLAIN:
		default:
			if (selected)
				{
				list = collection_table_selection_get_list(ct);
				}
			else
				{
				list = g_list_append(NULL, file_data_ref(ct->click_info->fd));
				}
			if (!list) return;

			uri_text = uri_text_from_filelist(list, &total, (info == TARGET_TEXT_PLAIN));
			filelist_free(list);
			break;
		}

	gtk_selection_data_set(selection_data, selection_data->target,
			       8, (guchar *)uri_text, total);
	g_free(uri_text);
}
