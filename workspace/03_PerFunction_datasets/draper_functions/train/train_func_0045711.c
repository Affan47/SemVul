playlist_add_url_string(gint argc, gchar **argv)
{
    gchar *uri;

	if (argc < 2)
	{
		audtool_whine_args(argv[0], "<url>");
		exit(1);
	}

    uri = construct_uri(argv[1]);
    if (uri) {
        audacious_remote_playlist_add_url_string(dbus_proxy, uri);
    }
    g_free(uri);
}
