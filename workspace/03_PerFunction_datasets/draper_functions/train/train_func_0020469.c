get_current_song_tuple_field_data(gint argc, gchar **argv)
{
	gchar *data;

	if (argc < 2)
	{
		audtool_whine_args(argv[0], "<fieldname>");
		audtool_whine_tuple_fields();
		exit(1);
	}

	if (!(data = audacious_get_tuple_field_data(dbus_proxy, argv[1], audacious_remote_get_playlist_pos(dbus_proxy))))
	{
		return;
	}

	audtool_report("%s", data);

	g_free(data);
}
