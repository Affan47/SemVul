brasero_volume_umount (BraseroVolume *volume,
		       gboolean wait,
		       GError **error)
{
	gboolean result;
	GVolume *gvolume;
	BraseroVolumePrivate *priv;

	if (!volume)
		return TRUE;

	g_return_val_if_fail (BRASERO_IS_VOLUME (volume), FALSE);

	priv = BRASERO_VOLUME_PRIVATE (volume);

	gvolume = brasero_volume_get_gvolume (volume);
	if (!gvolume)
		return TRUE;

	if (g_cancellable_is_cancelled (priv->cancel)) {
		BRASERO_MEDIA_LOG ("Resetting GCancellable object");
		g_cancellable_reset (priv->cancel);
	}

	result = brasero_gio_operation_umount (gvolume,
					       priv->cancel,
					       wait,
					       error);
	g_object_unref (gvolume);

	return result;
}
