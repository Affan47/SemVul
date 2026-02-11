_remove(CMD_ARGS)
{
	if (_switches[FORCE_ARG] && argc > 1)
		(void) _error_device(cmd, argc, argv, NULL, 0);

	return _simple(DM_DEVICE_REMOVE, argc > 1 ? argv[1] : NULL, 0, 0);
}
