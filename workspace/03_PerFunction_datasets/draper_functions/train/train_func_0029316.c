log_init(void)
{
	char   *device;
	size_t  size;

	if (!(device = rindex(setup.modem.device, '/')))
		device = setup.modem.device;
	else
		device++;

	size = (strlen(LOGFILEDIR) + strlen("vboxgetty-.log") + strlen(device) + 2);

	if ((setup.logname = (char *)malloc(size))) {
		printstring(setup.logname, "%s/vboxgetty-%s.log", LOGFILEDIR, device);

		if ((logsio = fopen(setup.logname, "a"))) {
			log_debuglevel(L_DEFAULT);
			returnok();
		} else {
			log(L_STDERR, "%s: Can't open log '%s'.\n", vbasename, setup.logname);
		}
	} else {
		log(L_STDERR, "%s: Not enough memory to allocate logname.\n", vbasename);
	}

	returnerror();
}
