instcmd(const char *cmdname, const char *extra)
{
	if (!strcasecmp(cmdname, "load.off")) {
		etapro_set_off_timer(1);
		return STAT_INSTCMD_HANDLED;
	}

	if (!strcasecmp(cmdname, "load.on")) {
		etapro_set_on_timer(1);
		return STAT_INSTCMD_HANDLED;
	}

	if (!strcasecmp(cmdname, "shutdown.return")) {
		upsdrv_shutdown();
		return STAT_INSTCMD_HANDLED;
	}

	upslogx(LOG_NOTICE, "instcmd: unknown command [%s]", cmdname);
	return STAT_INSTCMD_UNKNOWN;
}
