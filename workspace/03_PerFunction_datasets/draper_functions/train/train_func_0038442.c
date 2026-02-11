record_tick_callback (GSRWindow *window)
{
	GstElement *pipeline;
	GstFormat format = GST_FORMAT_TIME;
	gint64 val = -1;
	gint secs;


	if (window->priv->record->state != GST_STATE_PLAYING) {
		GST_DEBUG ("pipeline in wrong state: %s",
			gst_element_state_get_name (window->priv->record->state));
		return FALSE;
    }

	if (window->priv->seek_in_progress)
		return TRUE;

	pipeline = window->priv->record->pipeline;

	if (gst_element_query_position (pipeline, &format, &val) && val != -1) {
		gchar* len_str;

		secs = val / GST_SECOND;

		len_str = seconds_to_full_string (secs);
		window->priv->len_secs = secs;
		gtk_label_set_text (GTK_LABEL (window->priv->length_label),
				    len_str);
		g_free (len_str);
	} else {
		GST_DEBUG ("failed to query position");
	}

	return TRUE;
}
