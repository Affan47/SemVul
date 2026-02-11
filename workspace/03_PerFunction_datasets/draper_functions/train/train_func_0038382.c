_zmp_telnet(telnet_t *telnet, const char* buffer, size_t size) {
	telnet_event_t ev;
	const char **argv;
	const char *c;
	size_t i, argc;


	if (size == 0 || buffer[size - 1] != 0) {
		_error(telnet, __LINE__, __func__, TELNET_EPROTOCOL, 0,
				"incomplete ZMP frame");
		return 0;
	}


	for (argc = 0, c = buffer; c != buffer + size; ++argc)
		c += strlen(c) + 1;


	if ((argv = (const char **)calloc(argc, sizeof(char *))) == 0) {
		_error(telnet, __LINE__, __func__, TELNET_ENOMEM, 0,
				"calloc() failed: %s", strerror(errno));
		return 0;
	}


	for (i = 0, c = buffer; i != argc; ++i) {
		argv[i] = c;
		c += strlen(c) + 1;
	}


	ev.type = TELNET_EV_ZMP;
	ev.zmp.argv = argv;
	ev.zmp.argc = argc;
	telnet->eh(telnet, &ev, telnet->ud);


	free(argv);
	return 0;
}
