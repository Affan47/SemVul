ay_get_last_version(void)
{
	AyConnection *con = NULL;
	int connect_tag = 0;
	char *version = NULL;
	struct version_data *data = g_new0(struct version_data, 1);

	con = ay_connection_new("ayttm.sourceforge.net", 80,
		AY_CONNECTION_TYPE_PLAIN);

	data->tag = ay_connection_connect(con, ay_got_version_connection, NULL,
		NULL, data);

	connect_tag = ay_activity_bar_add(
		_("Getting latest version information"),
		ay_version_cancel_connect, data);

	while(!data->done)
		gtk_main_iteration();

	ay_activity_bar_remove(connect_tag);

	version = data->version;

	g_free(data);

	return version;
}
