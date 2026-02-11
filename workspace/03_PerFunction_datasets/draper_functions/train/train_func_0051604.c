instcmd_chktime(apc_cmdtab_t *ct)
{
	double	elapsed;
	time_t	now;
	static	time_t	last = 0;

	time(&now);

	elapsed = difftime(now, last);
	last = now;


	if ((elapsed < MINCMDTIME) || (elapsed > MAXCMDTIME)) {
		upsdebugx(1, "instcmd_chktime: outside window for %s (%2.0f)",
				ct->name, elapsed);
		return STAT_INSTCMD_HANDLED;
	}

	return do_cmd(ct);
}
