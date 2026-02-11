ch_ccmx_set_calibration_cb (GObject *source,
			    GAsyncResult *res,
			    gpointer user_data)
{
	ChCcmxPrivate *priv = (ChCcmxPrivate *) user_data;
	gboolean ret;
	GError *error = NULL;
	GtkWidget *widget;
	ChDeviceQueue *device_queue = CH_DEVICE_QUEUE (source);


	ret = ch_device_queue_process_finish (device_queue, res, &error);
	if (!ret) {
		ch_ccmx_error_dialog (priv,
				       _("Failed to set the calibration matrix"),
				       error->message);
		g_error_free (error);
		goto out;
	}


	widget = GTK_WIDGET (gtk_builder_get_object (priv->builder, "button_close"));
	gtk_widget_set_sensitive (widget, FALSE);


	ch_device_queue_set_calibration_map (priv->device_queue,
					     priv->device,
					     priv->calibration_map);
	ch_device_queue_process_async (priv->device_queue,
				       CH_DEVICE_QUEUE_PROCESS_FLAGS_NONE,
				       NULL,
				       ch_ccmx_set_calibration_map_cb,
				       priv);
out:
	return;
}
