drag_data_received_callback (GtkWidget *widget,
			     GdkDragContext *context,
			     int x,
			     int y,
			     GtkSelectionData *selection_data,
			     guint info,
			     guint32 time,
			     gpointer data)
{
	NemoTreeViewDragDest *dest;
	const char *tmp;
	int length;
	gboolean success, finished;

	dest = NEMO_TREE_VIEW_DRAG_DEST (data);

	if (!dest->details->have_drag_data) {
		dest->details->have_drag_data = TRUE;
		dest->details->drag_type = info;
		dest->details->drag_data =
			gtk_selection_data_copy (selection_data);
		if (info == NEMO_ICON_DND_GNOME_ICON_LIST) {
			dest->details->drag_list =
				nemo_drag_build_selection_list (selection_data);
		}
	}

	if (dest->details->drop_occurred) {
		success = FALSE;
		finished = TRUE;
		switch (info) {
		case NEMO_ICON_DND_GNOME_ICON_LIST :
			receive_dropped_icons (dest, context, x, y);
			success = TRUE;
			break;
		case NEMO_ICON_DND_NETSCAPE_URL :
			receive_dropped_netscape_url (dest, context, x, y);
			success = TRUE;
			break;
		case NEMO_ICON_DND_URI_LIST :
			receive_dropped_uri_list (dest, context, x, y);
			success = TRUE;
			break;
		case NEMO_ICON_DND_TEXT:
			receive_dropped_text (dest, context, x, y);
			success = TRUE;
			break;
		case NEMO_ICON_DND_RAW:
			length = gtk_selection_data_get_length (selection_data);
			tmp = gtk_selection_data_get_data (selection_data);
			receive_dropped_raw (dest, tmp, length, context, x, y);
			success = TRUE;
			break;
		case NEMO_ICON_DND_XDNDDIRECTSAVE:
			finished = receive_xds (dest, widget, time, context, x, y);
			success = TRUE;
			break;
		}

		if (finished) {
			dest->details->drop_occurred = FALSE;
			free_drag_data (dest);
			gtk_drag_finish (context, success, FALSE, time);
		}
	}


	g_signal_stop_emission_by_name (dest->details->tree_view,
					"drag_data_received");

	return TRUE;
}
