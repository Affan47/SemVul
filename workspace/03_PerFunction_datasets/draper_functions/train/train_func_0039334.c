brasero_medium_probe_thread (gpointer self)
{
	gint counter = 0;
	GTimeVal wait_time;
	const gchar *device;
	BraseroScsiErrCode code;
	BraseroMediumPrivate *priv;
	BraseroDeviceHandle *handle;

	priv = BRASERO_MEDIUM_PRIVATE (self);

	priv->info = BRASERO_MEDIUM_BUSY;


	device = brasero_drive_get_device (priv->drive);
	BRASERO_MEDIA_LOG ("Trying to open device %s", device);

	handle = brasero_device_handle_open (device, FALSE, &code);
	while (!handle && counter <= BRASERO_MEDIUM_OPEN_ATTEMPTS) {
		sleep (1);

		if (priv->probe_cancelled)
			goto end;

		counter ++;
		handle = brasero_device_handle_open (device, FALSE, &code);
	}

	if (!handle) {
		BRASERO_MEDIA_LOG ("Open () failed: medium busy");
		goto end;
	}

	if (priv->probe_cancelled) {
		brasero_device_handle_close (handle);
		goto end;
	}

	BRASERO_MEDIA_LOG ("Open () succeeded");


	while (brasero_spc1_test_unit_ready (handle, &code) != BRASERO_SCSI_OK) {
		if (code == BRASERO_SCSI_NO_MEDIUM) {
			BRASERO_MEDIA_LOG ("No medium inserted");
			priv->info = BRASERO_MEDIUM_NONE;

			brasero_device_handle_close (handle);
			goto end;
		}
		else if (code != BRASERO_SCSI_NOT_READY) {
			BRASERO_MEDIA_LOG ("Device does not respond");

			brasero_device_handle_close (handle);
			goto end;
		}

		g_get_current_time (&wait_time);
		g_time_val_add (&wait_time, 2000000);

		g_mutex_lock (priv->mutex);
		g_cond_timed_wait (priv->cond_probe,
		                   priv->mutex,
		                   &wait_time);
		g_mutex_unlock (priv->mutex);

		if (priv->probe_cancelled) {
			BRASERO_MEDIA_LOG ("Device probing cancelled");

			brasero_device_handle_close (handle);
			goto end;
		}
	}

	BRASERO_MEDIA_LOG ("Device ready");

	brasero_medium_init_real (BRASERO_MEDIUM (self), handle);
	brasero_device_handle_close (handle);

end:

	g_mutex_lock (priv->mutex);

	priv->probe = NULL;
	if (!priv->probe_cancelled)
		priv->probe_id = g_idle_add (brasero_medium_probed, self);

	g_cond_broadcast (priv->cond);
	g_mutex_unlock (priv->mutex);

	g_thread_exit (0);

	return NULL;
}
