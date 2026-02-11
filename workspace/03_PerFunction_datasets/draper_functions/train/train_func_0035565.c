handle_speechcreate(struct ast_channel *chan, AGI *agi, int argc, const char * const argv[])
{
	struct ast_format_cap *cap;
	struct ast_format tmpfmt;


	if (agi->speech) {
		ast_agi_send(agi->fd, chan, "200 result=0\n");
		return RESULT_SUCCESS;
	}

	if (!(cap = ast_format_cap_alloc_nolock())) {
		return RESULT_FAILURE;
	}
	ast_format_cap_add(cap, ast_format_set(&tmpfmt, AST_FORMAT_SLINEAR, 0));
	if ((agi->speech = ast_speech_new(argv[2], cap))) {
		ast_agi_send(agi->fd, chan, "200 result=1\n");
	} else {
		ast_agi_send(agi->fd, chan, "200 result=0\n");
	}
	cap = ast_format_cap_destroy(cap);

	return RESULT_SUCCESS;
}
