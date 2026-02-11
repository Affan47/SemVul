update_attached_to (GtkSourceCompletionInfo *info)
{
	GtkWidget *attached_to = gtk_window_get_attached_to (GTK_WINDOW (info));

	if (info->priv->focus_out_event_handler != 0 &&
	    info->priv->attached_to != NULL)
	{
		g_signal_handler_disconnect (info->priv->attached_to,
					     info->priv->focus_out_event_handler);

		info->priv->focus_out_event_handler = 0;
	}

	info->priv->attached_to = attached_to;

	if (attached_to == NULL)
	{
		return;
	}

	g_object_add_weak_pointer (G_OBJECT (attached_to),
				   (gpointer) &info->priv->attached_to);

	info->priv->focus_out_event_handler = g_signal_connect_swapped (attached_to,
									"focus-out-event",
									G_CALLBACK (focus_out_event_cb),
									info);
}
