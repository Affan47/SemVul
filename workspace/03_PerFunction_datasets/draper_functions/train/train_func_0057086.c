brasero_drive_reprobe (BraseroDrive *drive)
{
	BraseroDrivePrivate *priv;
	BraseroMedium *medium;

	g_return_if_fail (drive != NULL);
	g_return_if_fail (BRASERO_IS_DRIVE (drive));

	priv = BRASERO_DRIVE_PRIVATE (drive);

	if (priv->gdrive) {

		g_drive_poll_for_media (priv->gdrive, NULL, NULL, NULL);
	}

	priv->probe_waiting = FALSE;

	BRASERO_MEDIA_LOG ("Reprobing inserted medium");
	if (priv->medium) {

		medium = priv->medium;
		priv->medium = NULL;

		g_signal_emit (drive,
			       drive_signals [MEDIUM_REMOVED],
			       0,
			       medium);
		g_object_unref (medium);
	}

	brasero_drive_probe_inside (drive);
}
