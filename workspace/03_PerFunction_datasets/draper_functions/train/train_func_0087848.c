cmd_cancel_scan (SANE_Handle handle)
{
	Magicolor_Scanner *s = (Magicolor_Scanner *) handle;
	SANE_Status status;
	unsigned char *buf;
	size_t buflen;

	DBG(8, "%s\n", __func__);
	buflen = mc_create_buffer (s, s->hw->cmd->scanner_cmd, s->hw->cmd->stop_scanning,
				    &buf, NULL, 0, &status);
	if (buflen <= 0 ) {
		return SANE_STATUS_NO_MEM;
	} else if (status != SANE_STATUS_GOOD) {
		return status;
	}

	mc_send(s, buf, buflen, &status);
	free (buf);
	if (status != SANE_STATUS_GOOD)
		DBG(8, "%s: Data NOT successfully sent\n", __func__);
	else
		DBG(8, "%s: Data successfully sent\n", __func__);
	return status;
}
