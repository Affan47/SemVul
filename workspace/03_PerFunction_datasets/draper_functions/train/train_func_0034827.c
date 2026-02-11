_wait(CMD_ARGS)
{
	const char *name = NULL;

	if (!_switches[UUID_ARG] && !_switches[MAJOR_ARG]) {
		if (argc == 1) {
			err("No device specified.");
			return 0;
		}
		name = argv[1];
		argc--, argv++;
	}

	return _simple(DM_DEVICE_WAITEVENT, name,
		       (argc > 1) ? (uint32_t) atoi(argv[argc - 1]) : 0, 1);
}
