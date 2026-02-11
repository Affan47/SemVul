cd_device_string_remove_suffix (gchar *vendor, const gchar *suffix)
{
	g_strchomp (vendor);
	if (g_str_has_suffix (vendor, suffix)) {
		gint len, suffix_len;
		len = strlen (vendor);
		suffix_len = strlen (suffix);
		vendor[len - suffix_len] = '\0';
	}
	g_strchomp (vendor);
}
