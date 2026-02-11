entry_drag_data_received (GtkEditable      *entry,
			  GdkDragContext   *context,
			  gint              x,
			  gint              y,
			  GtkSelectionData *selection_data,
			  guint             info,
			  guint32           time,
			  PanelRunDialog   *dialog)
{
	char **uris;
	char  *file;
	int    i;

        if (gtk_selection_data_get_format (selection_data) != 8 || gtk_selection_data_get_length (selection_data) == 0) {
        	g_warning (_("URI list dropped on run dialog had wrong format (%d) or length (%d)\n"),
			   gtk_selection_data_get_format (selection_data),
			   gtk_selection_data_get_length (selection_data));
		return;
        }

	uris = g_uri_list_extract_uris ((const char *)gtk_selection_data_get_data (selection_data));

	if (!uris) {
		gtk_drag_finish (context, FALSE, FALSE, time);
		return;
	}

	for (i = 0; uris [i]; i++) {
		if (!uris [i] || !uris [i][0])
			continue;

		file = g_filename_from_uri (uris [i], NULL, NULL);


		if (file) {
			panel_run_dialog_append_file_utf8 (dialog, file);
			g_free (file);
		} else
			panel_run_dialog_append_file_utf8 (dialog, uris [i]);
	}

	g_strfreev (uris);
	gtk_drag_finish (context, TRUE, FALSE, time);
}
