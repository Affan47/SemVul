brasero_medium_init_real (BraseroMedium *object,
			  BraseroDeviceHandle *handle)
{
	guint i;
	gchar *name;
	gboolean result;
	BraseroMediumPrivate *priv;
	BraseroScsiErrCode code = 0;
	gchar buffer [256] = { 0, };

	priv = BRASERO_MEDIUM_PRIVATE (object);

	name = brasero_drive_get_display_name (priv->drive);
	BRASERO_MEDIA_LOG ("Initializing information for medium in %s", name);
	g_free (name);

	if (priv->probe_cancelled)
		return;

	result = brasero_medium_get_medium_type (object, handle, &code);
	if (result != TRUE)
		return;

	if (priv->probe_cancelled)
		return;

	result = brasero_medium_get_speed (object, handle, &code);
	if (result != TRUE)
		return;

	if (priv->probe_cancelled)
		return;

	brasero_medium_get_capacity_by_type (object, handle, &code);
	if (priv->probe_cancelled)
		return;

	brasero_medium_init_caps (object, handle, &code);
	if (priv->probe_cancelled)
		return;

	if (!brasero_medium_get_contents (object, handle, &code))
		return;

	if (priv->probe_cancelled)
		return;


	if (BRASERO_MEDIUM_IS (priv->info, (BRASERO_MEDIUM_DVD|BRASERO_MEDIUM_ROM)))
		brasero_medium_get_css_feature (object, handle, &code);

	if (priv->probe_cancelled)
		return;


	if (priv->info & BRASERO_MEDIUM_HAS_AUDIO)
		brasero_medium_read_CD_TEXT (object, handle, &code);

	if (priv->probe_cancelled)
		return;

	brasero_media_to_string (priv->info, buffer);
	BRASERO_MEDIA_LOG ("media is %s", buffer);

	if (!priv->wr_speeds)
		return;


	for (i = 0; priv->wr_speeds [i] != 0; i ++) {
		guint j;

		for (j = 0; priv->wr_speeds [j] != 0; j ++) {
			if (priv->wr_speeds [i] > priv->wr_speeds [j]) {
				gint64 tmp;

				tmp = priv->wr_speeds [i];
				priv->wr_speeds [i] = priv->wr_speeds [j];
				priv->wr_speeds [j] = tmp;
			}
		}
	}
}
