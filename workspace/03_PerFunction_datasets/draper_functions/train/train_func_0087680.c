handle_setpriority(struct ast_channel *chan, AGI *agi, int argc, const char * const argv[])
{
	int pri;

	if (argc != 3)
		return RESULT_SHOWUSAGE;

	if (sscanf(argv[2], "%30d", &pri) != 1) {
		pri = ast_findlabel_extension(chan, ast_channel_context(chan), ast_channel_exten(chan), argv[2],
			S_COR(ast_channel_caller(chan)->id.number.valid, ast_channel_caller(chan)->id.number.str, NULL));
		if (pri < 1)
			return RESULT_SHOWUSAGE;
	}

	ast_explicit_goto(chan, NULL, NULL, pri);
	ast_agi_send(agi->fd, chan, "200 result=0\n");
	return RESULT_SUCCESS;
}
