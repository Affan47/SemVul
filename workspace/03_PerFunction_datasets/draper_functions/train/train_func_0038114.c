instcmd(const char *cmdname, const char *extra)
{

	if (!strcasecmp(cmdname, "shutdown.return"))  {

		ser_send_char(upsfd, CMD_SHUTRET);

		return STAT_INSTCMD_HANDLED;
	}

	if (!strcasecmp(cmdname, "shutdown.stayoff"))
	  {

	    ser_send_char(upsfd, CMD_SHUT);

	    return STAT_INSTCMD_HANDLED;
	  }

	upslogx(LOG_NOTICE, "instcmd: unknown command [%s]", cmdname);
	return STAT_INSTCMD_UNKNOWN;

}
