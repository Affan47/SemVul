vflist_dnd_get(GtkWidget *widget, GdkDragContext *context,
			   GtkSelectionData *selection_data, guint info,
			   guint time, gpointer data)
{
	ViewFile *vf = data;
	GList *list = NULL;
	gchar *uri_text = NULL;
	gint total;

	if (!VFLIST(vf)->click_fd) return;

	if (vflist_row_is_selected(vf, VFLIST(vf)->click_fd))
		{
		list = vf_selection_get_list(vf);
		}
	else
		{
		list = g_list_append(NULL, file_data_ref(VFLIST(vf)->click_fd));
		}

	if (!list) return;

	uri_text = uri_text_from_filelist(list, &total, (info == TARGET_TEXT_PLAIN));
	filelist_free(list);

	DEBUG_1("%s", uri_text);

	gtk_selection_data_set(selection_data, selection_data->target,
			       8, (guchar *)uri_text, total);
	g_free(uri_text);
}
