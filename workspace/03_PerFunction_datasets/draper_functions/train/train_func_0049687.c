ch_ccmx_set_calibration_map_cb (GObject *source,
				GAsyncResult *res,
				gpointer user_data)
{
	const gchar *title;
	ChCcmxPrivate *priv = (ChCcmxPrivate *) user_data;
	gboolean ret;
	GError *error = NULL;
	GtkWidget *widget;
	ChDeviceQueue *device_queue = CH_DEVICE_QUEUE (source);


	ret = ch_device_queue_process_finish (device_queue, res, &error);
	if (!ret) {


		title = _("Failed to set the calibration map");
		ch_ccmx_error_dialog (priv, title, error->message);
		g_error_free (error);
		goto out;
	}


	ch_ccmx_refresh_calibration_data (priv);
out:

	widget = GTK_WIDGET (gtk_builder_get_object (priv->builder, "button_close"));
	gtk_widget_set_sensitive (widget, TRUE);
}
