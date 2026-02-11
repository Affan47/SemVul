eagi_exec(struct ast_channel *chan, const char *data)
{
	int res;
	struct ast_format readformat;

	if (ast_check_hangup(chan)) {
		ast_log(LOG_ERROR, "EAGI cannot be run on a dead/hungup channel, please use AGI.\n");
		return 0;
	}
	ast_format_copy(&readformat, ast_channel_readformat(chan));
	if (ast_set_read_format_by_id(chan, AST_FORMAT_SLINEAR)) {
		ast_log(LOG_WARNING, "Unable to set channel '%s' to linear mode\n", ast_channel_name(chan));
		return -1;
	}
	res = agi_exec_full(chan, data, 1, 0);
	if (!res) {
		if (ast_set_read_format(chan, &readformat)) {
			ast_log(LOG_WARNING, "Unable to restore channel '%s' to format %s\n", ast_channel_name(chan), ast_getformatname(&readformat));
		}
	}
	return res;
}
