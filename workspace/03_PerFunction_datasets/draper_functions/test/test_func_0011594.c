drop_playlist_cb (GtkWidget     *widget,
	       GdkDragContext     *context,
	       gint                x,
	       gint                y,
	       GtkSelectionData   *data,
	       guint               info,
	       guint               _time,
	       Totem              *totem)
{
	gboolean empty_pl;
	GdkDragAction action = gdk_drag_context_get_selected_action (context);

	if (action == GDK_ACTION_ASK) {
		action = totem_drag_ask (totem_get_playlist_length (totem) > 0);
		gdk_drag_status (context, action, GDK_CURRENT_TIME);
	}

	if (action == GDK_ACTION_DEFAULT) {
		gtk_drag_finish (context, FALSE, FALSE, _time);
		return;
	}

	empty_pl = (action == GDK_ACTION_MOVE);

	totem_action_drop_files (totem, data, info, empty_pl);
	gtk_drag_finish (context, TRUE, FALSE, _time);
}
