seahorse_util_detect_data_type (const gchar *data, guint length)
{
	gboolean uncertain;
	gchar *mime;
	GQuark type;

	mime = g_content_type_guess (NULL, (const guchar*)data, length, &uncertain);
	g_return_val_if_fail (mime, 0);

	type = seahorse_util_detect_mime_type (mime);
	g_free (mime);

	return type;
}
