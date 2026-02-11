brasero_drive_update_gdrive (BraseroDrive *drive,
                             GDrive *gdrive)
{
	BraseroDrivePrivate *priv;

	priv = BRASERO_DRIVE_PRIVATE (drive);
	if (priv->gdrive) {
		g_signal_handlers_disconnect_by_func (priv->gdrive,
						      brasero_drive_medium_gdrive_changed_cb,
						      drive);


		g_cancellable_cancel (priv->cancel);

		g_object_unref (priv->gdrive);
		priv->gdrive = NULL;
	}

	BRASERO_MEDIA_LOG ("Setting GDrive %p", gdrive);

	if (gdrive) {
		priv->gdrive = g_object_ref (gdrive);


		g_signal_connect (priv->gdrive,
				  "changed",
				  G_CALLBACK (brasero_drive_medium_gdrive_changed_cb),
				  drive);
	}

	if (priv->locked || priv->ejecting) {
		BRASERO_MEDIA_LOG ("Waiting for next unlocking of the drive to probe");


		priv->probe_waiting = TRUE;
		return;
	}

	brasero_drive_probe_inside (drive);
}
