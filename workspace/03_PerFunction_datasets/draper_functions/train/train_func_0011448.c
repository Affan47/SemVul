brasero_drive_probe_inside_thread (gpointer data)
{
	gint counter = 0;
	GTimeVal wait_time;
	const gchar *device;
	BraseroScsiErrCode code;
	BraseroDrivePrivate *priv;
	BraseroDeviceHandle *handle = NULL;
	BraseroDrive *drive = BRASERO_DRIVE (data);

	priv = BRASERO_DRIVE_PRIVATE (drive);


	device = brasero_drive_get_device (drive);
	BRASERO_MEDIA_LOG ("Trying to open device %s", device);

	priv->has_medium = FALSE;

	handle = brasero_device_handle_open (device, FALSE, &code);
	while (!handle && counter <= BRASERO_DRIVE_OPEN_ATTEMPTS) {
		sleep (1);

		if (priv->probe_cancelled) {
			BRASERO_MEDIA_LOG ("Open () cancelled");
			goto end;
		}

		counter ++;
		handle = brasero_device_handle_open (device, FALSE, &code);
	}

	if (!handle) {
		BRASERO_MEDIA_LOG ("Open () failed: medium busy");
		goto end;
	}

	if (priv->probe_cancelled) {
		BRASERO_MEDIA_LOG ("Open () cancelled");

		brasero_device_handle_close (handle);
		goto end;
	}

	while (brasero_spc1_test_unit_ready (handle, &code) != BRASERO_SCSI_OK) {
		if (code == BRASERO_SCSI_NO_MEDIUM) {
			BRASERO_MEDIA_LOG ("No medium inserted");

			brasero_device_handle_close (handle);
			goto end;
		}

		if (code != BRASERO_SCSI_NOT_READY) {
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

	BRASERO_MEDIA_LOG ("Medium inserted");
	brasero_device_handle_close (handle);

	priv->has_medium = TRUE;

end:

	g_mutex_lock (priv->mutex);

	if (!priv->probe_cancelled)
		priv->probe_id = g_idle_add (brasero_drive_probed_inside, drive);

	priv->probe = NULL;
	g_cond_broadcast (priv->cond);
	g_mutex_unlock (priv->mutex);

	g_thread_exit (0);

	return NULL;
}
