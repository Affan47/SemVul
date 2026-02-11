do_cmd(const apc_cmdtab_t *ct)
{
	int ret;
	char temp[APC_LBUF];
	const char *strerr;

	apc_flush(SER_AA);

	if (ct->flags & APC_REPEAT) {
		ret = apc_write_rep(ct->cmd);
		strerr = "apc_write_rep";
	} else {
		ret = apc_write(ct->cmd);
		strerr = "apc_write";
	}

	if (ret < 1) {
		upslog_with_errno(LOG_ERR, "do_cmd: %s failed", strerr);
		return STAT_INSTCMD_FAILED;
	}

	ret = apc_read(temp, sizeof(temp), SER_AA);

	if (ret < 1)
		return STAT_INSTCMD_FAILED;

	if (strcmp(temp, "OK")) {
		upslogx(LOG_WARNING, "got [%s] after command [%s]",
			temp, ct->name);

		return STAT_INSTCMD_FAILED;
	}

	upslogx(LOG_INFO, "command: %s", ct->name);
	return STAT_INSTCMD_HANDLED;
}
