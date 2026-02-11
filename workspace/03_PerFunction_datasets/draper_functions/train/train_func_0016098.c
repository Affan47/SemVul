tracker_xmp_read (const gchar    *buffer,
                  size_t          len,
                  const gchar    *uri,
                  TrackerXmpData *data)
{
	g_return_val_if_fail (buffer != NULL, FALSE);
	g_return_val_if_fail (len > 0, FALSE);
	g_return_val_if_fail (uri != NULL, FALSE);
	g_return_val_if_fail (data != NULL, FALSE);

	return parse_xmp (buffer, len, uri, data);
}
