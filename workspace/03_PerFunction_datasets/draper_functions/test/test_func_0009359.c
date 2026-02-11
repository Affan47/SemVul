dl_send_at_command(const struct psock * sock, const uint8_t * cmd)
{
	unsigned int flag;
	if (sock == NULL || !is_ps_valid(sock))
		goto err;

	flag = sock->flags & (PS_FLAG_LOCAL | PS_FLAG_REMOTE);


	if (flag == 0 || flag == (PS_FLAG_LOCAL | PS_FLAG_REMOTE))
		goto err;

	(flag == PS_FLAG_LOCAL ? dl_local_at_command : dl_remote_at_command)(sock, cmd);
	return 0;

err:
	dbg("send_at_command invalid socket!\n");
	return -1;
}
