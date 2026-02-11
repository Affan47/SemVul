ch_util_flash_firmware (ChUtilPrivate *priv, gchar **values, GError **error)
{
	gboolean ret;


	if (g_strv_length (values) != 1) {
		ret = FALSE;
		g_set_error_literal (error, 1, 0,
				     "invalid input, expect 'filename'");
		goto out;
	}


	g_print ("WARNING: Do not shutdown the computer or unplug the device.\n");


	ret = ch_util_get_prompt (_("Flash the device?"), FALSE);
	if (!ret) {
		g_set_error_literal (error, 1, 0,
				     "user declined");
		goto out;
	}


	ret = ch_util_flash_firmware_internal (priv,
					       values[0],
					       error);
	if (!ret)
		goto out;


	g_print ("INFO: Flashing was successful.\n");
out:
	return ret;
}
