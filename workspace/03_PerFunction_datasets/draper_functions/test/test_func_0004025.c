handle_tddmode(struct ast_channel *chan, AGI *agi, int argc, const char * const argv[])
{
	int res, x;

	if (argc != 3)
		return RESULT_SHOWUSAGE;

	if (!strncasecmp(argv[2],"on",2)) {
		x = 1;
	} else  {
		x = 0;
	}
	if (!strncasecmp(argv[2],"mate",4))  {
		x = 2;
	}
	if (!strncasecmp(argv[2],"tdd",3)) {
		x = 1;
	}
	res = ast_channel_setoption(chan, AST_OPTION_TDD, &x, sizeof(char), 0);
	if (res) {

		ast_agi_send(agi->fd, chan, "200 result=0\n");
	} else {
		ast_agi_send(agi->fd, chan, "200 result=1\n");
	}
	return RESULT_SUCCESS;
}
