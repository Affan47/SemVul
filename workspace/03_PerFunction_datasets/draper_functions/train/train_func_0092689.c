instcmd(const char *cmdname, const char *extra)
{
	const char	*val;

	val = dstate_getinfo(getval("load.status"));
	if (val) {
		if (!strcasecmp(val, "off") || !strcasecmp(val, "no")) {
			outlet = 0;
		}

		if (!strcasecmp(val, "on") || !strcasecmp(val, "yes")) {
			outlet = 1;
		}
	}

	if (!strcasecmp(cmdname, "shutdown.return")) {
		if (outlet && (ups.timer.shutdown < 0)) {
			ups.timer.shutdown = offdelay;
			dstate_setinfo("ups.status", "FSD %s", ups.status);
		}
		ups.timer.start = ondelay;
		return STAT_INSTCMD_HANDLED;
	}

	if (!strcasecmp(cmdname, "shutdown.stayoff")) {
		if (outlet && (ups.timer.shutdown < 0)) {
			ups.timer.shutdown = offdelay;
			dstate_setinfo("ups.status", "FSD %s", ups.status);
		}
		ups.timer.start = -1;
		return STAT_INSTCMD_HANDLED;
	}

	upslogx(LOG_NOTICE, "instcmd: unknown command [%s]", cmdname);
	return STAT_INSTCMD_UNKNOWN;
}
