string_to_ssid (const char *str)
{
	GByteArray *ssid;

	g_assert (str != NULL);

	ssid = g_byte_array_sized_new (strlen (str));
	g_assert (ssid != NULL);
	g_byte_array_append (ssid, (const guint8 *) str, strlen (str));
	return ssid;
}
