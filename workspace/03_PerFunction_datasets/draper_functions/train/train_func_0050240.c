brasero_drive_medium_gdrive_changed_cb (BraseroDrive *gdrive,
					BraseroDrive *drive)
{
	BraseroDrivePrivate *priv;

	priv = BRASERO_DRIVE_PRIVATE (drive);
	if (priv->locked || priv->ejecting) {
		BRASERO_MEDIA_LOG ("Waiting for next unlocking of the drive to probe");


		priv->probe_waiting = TRUE;
		return;
	}

	BRASERO_MEDIA_LOG ("GDrive changed");
	brasero_drive_probe_inside (drive);
}
