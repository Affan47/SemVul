send_cmdline_tail(struct telnet_client_t *cln, int corr)
{
	if (telnet_send(cln, cln->cmdline + cln->cmdline_pos, cln->cmdline_len - cln->cmdline_pos))
		return -1;

	memset(temp_buf, '\b', cln->cmdline_len - cln->cmdline_pos - corr);

	if (telnet_send(cln, temp_buf, cln->cmdline_len - cln->cmdline_pos - corr))
		return -1;

	return 0;
}
