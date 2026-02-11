xmms_diskwrite_write (xmms_output_t *output, gpointer buffer, gint len,
                      xmms_error_t *error)
{
	xmms_diskwrite_data_t *data;
#if G_BYTE_ORDER == G_BIG_ENDIAN
	gint16 *s = (gint16 *) buffer;
	gint i;
#endif

	g_return_if_fail (output);
	g_return_if_fail (buffer);
	g_return_if_fail (len > 0);

	data = xmms_output_private_data_get (output);
	g_return_if_fail (data);
	g_return_if_fail (data->fp);

#if G_BYTE_ORDER == G_BIG_ENDIAN
	for (i = 0; i < (len / 2); i++) {
		s[i] = GINT16_TO_LE (s[i]);
	}
#endif

	fwrite (buffer, sizeof (gchar), len, data->fp);
}
