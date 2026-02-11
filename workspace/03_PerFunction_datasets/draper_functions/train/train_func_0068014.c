main (int argc, char *argv[])
{
	parse_arguments (argc, argv);


	if ((client = jack_client_open ("freewheel", JackNullOption, NULL)) == 0) {
		fprintf (stderr, "JACK server not running?\n");
		exit(1);
	}

	signal (SIGQUIT, signal_handler);
	signal (SIGTERM, signal_handler);
	signal (SIGHUP, signal_handler);
	signal (SIGINT, signal_handler);

	jack_on_shutdown (client, jack_shutdown, 0);

	if (jack_set_freewheel (client, onoff)) {
		fprintf (stderr, "failed to reset freewheel mode\n");
	}

	jack_client_close(client);

	return 0;
}
