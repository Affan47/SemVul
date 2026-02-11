ch_util_set_remote_hash (ChUtilPrivate *priv, gchar **values, GError **error)
{
	gboolean ret;
	ChSha1 remote_hash;


	if (g_strv_length (values) != 1) {
		ret = FALSE;
		g_set_error_literal (error, 1, 0,
				     "invalid input, expect sha1");
		goto out;
	}


	ret = ch_sha1_parse (values[0], &remote_hash, error);
	if (!ret)
		goto out;


	ch_device_queue_set_remote_hash (priv->device_queue,
					 priv->device,
					 &remote_hash);
	ch_device_queue_write_eeprom (priv->device_queue,
				      priv->device,
				      CH_WRITE_EEPROM_MAGIC);
	ret = ch_device_queue_process (priv->device_queue,
				       CH_DEVICE_QUEUE_PROCESS_FLAGS_NONE,
				       NULL,
				       error);
	if (!ret)
		goto out;

out:
	return ret;
}
