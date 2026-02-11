playback_seek(gint argc, gchar **argv)
{
	if (argc < 2)
	{
		audtool_whine_args(argv[0], "<position>");
		exit(1);
	}

	audacious_remote_jump_to_time(dbus_proxy, atof(argv[1]) * 1000);
}
