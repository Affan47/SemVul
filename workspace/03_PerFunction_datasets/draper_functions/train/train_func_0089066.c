gfire_buddy_avatar_download_cb(PurpleUtilFetchUrlData *p_url_data, gpointer p_data, const char *p_buf, gsize p_len, const gchar *p_error_message)
{
	guchar *temp = NULL;

	if (p_data == NULL || p_buf == NULL || p_len == 0)
	{
		purple_debug(PURPLE_DEBUG_ERROR, "gfire", "gfire_avatar_download_cb: download of avatar failed (%s)\n", NN(p_error_message));
		return;
	}

	temp = g_malloc0(p_len);
	memcpy(temp, p_buf, p_len);

	gfire_buddy_set_avatar((gfire_buddy*)p_data, temp, p_len);
}
