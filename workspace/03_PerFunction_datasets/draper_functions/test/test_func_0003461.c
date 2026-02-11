esci_request_identity2(SANE_Handle handle, unsigned char **buf)
{
	Epson_Scanner *s = (Epson_Scanner *) handle;
	SANE_Status status;
	size_t len;
	unsigned char params[2];

	DBG(8, "%s\n", __func__);

	if (s->hw->cmd->request_identity2 == 0)
		return SANE_STATUS_UNSUPPORTED;

	params[0] = ESC;
	params[1] = s->hw->cmd->request_identity2;

	status = e2_cmd_info_block(s, params, 2, 0, buf, &len);
	if (status != SANE_STATUS_GOOD)
		return status;

	return status;
}
