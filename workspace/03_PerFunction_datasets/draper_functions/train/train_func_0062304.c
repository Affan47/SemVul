printf_mc_usage(void)
{
	struct bitfield_data * bf;
	lprintf(LOG_NOTICE, "MC Commands:");
	lprintf(LOG_NOTICE, "  reset <warm|cold>");
	lprintf(LOG_NOTICE, "  guid");
	lprintf(LOG_NOTICE, "  info");
	lprintf(LOG_NOTICE, "  watchdog <get|reset|off>");
	lprintf(LOG_NOTICE, "  selftest");
	lprintf(LOG_NOTICE, "  getenables");
	lprintf(LOG_NOTICE, "  setenables <option=on|off> ...");
	for (bf = mc_enables_bf; bf->name != NULL; bf++) {
		lprintf(LOG_NOTICE, "    %-20s  %s", bf->name, bf->desc);
	}
	printf_sysinfo_usage(0);
}
