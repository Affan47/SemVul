match_caltech_cb(void *user_data, void *arg, int flags)
{
	struct ast_calendar *cal = user_data;
	struct ast_calendar_tech *tech = arg;

	if (cal->tech == tech) {
		return CMP_MATCH;
	}

	return 0;
}
