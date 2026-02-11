handle_recvchar(struct ast_channel *chan, AGI *agi, int argc, const char * const argv[])
{
	int res;

	if (argc != 3)
		return RESULT_SHOWUSAGE;

	res = ast_recvchar(chan,atoi(argv[2]));
	if (res == 0) {
		ast_agi_send(agi->fd, chan, "200 result=%d (timeout)\n", res);
		return RESULT_SUCCESS;
	}
	if (res > 0) {
		ast_agi_send(agi->fd, chan, "200 result=%d\n", res);
		return RESULT_SUCCESS;
	}
	ast_agi_send(agi->fd, chan, "200 result=%d (hangup)\n", res);
	return RESULT_FAILURE;
}
