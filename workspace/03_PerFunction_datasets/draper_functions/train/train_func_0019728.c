wait_moh_exec(struct ast_channel *chan, const char *data)
{
	static int deprecation_warning = 0;
	int res;

	if (!deprecation_warning) {
		deprecation_warning = 1;
		ast_log(LOG_WARNING, "WaitMusicOnHold application is deprecated and will be removed. Use MusicOnHold with duration parameter instead\n");
	}

	if (!data || !atoi(data)) {
		ast_log(LOG_WARNING, "WaitMusicOnHold requires an argument (number of seconds to wait)\n");
		return -1;
	}
	if (ast_moh_start(chan, NULL, NULL)) {
		ast_log(LOG_WARNING, "Unable to start music on hold for %d seconds on channel %s\n", atoi(data), ast_channel_name(chan));
		return 0;
	}
	res = ast_safe_sleep(chan, atoi(data) * 1000);
	ast_moh_stop(chan);
	return res;
}
