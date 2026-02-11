measurement_cb(guint8 status, const guint8 *pdu,
						guint16 len, gpointer user_data)
{
	char *msg = user_data;

	if (status != 0)
		error("%s failed", msg);

	g_free(msg);
}
