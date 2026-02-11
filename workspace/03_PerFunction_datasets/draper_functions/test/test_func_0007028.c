cli_tps_ping(struct ast_cli_entry *e, int cmd, struct ast_cli_args *a)
{
	struct timeval begin, end, delta;
	const char *name;
	struct timeval when;
	struct timespec ts;
	struct ast_taskprocessor *tps = NULL;

	switch (cmd) {
	case CLI_INIT:
		e->command = "core ping taskprocessor";
		e->usage =
			"Usage: core ping taskprocessor <taskprocessor>\n"
			"	Displays the time required for a task to be processed\n";
		return NULL;
	case CLI_GENERATE:
		return tps_taskprocessor_tab_complete(tps, a);
	}

	if (a->argc != 4)
		return CLI_SHOWUSAGE;

	name = a->argv[3];
	if (!(tps = ast_taskprocessor_get(name, TPS_REF_IF_EXISTS))) {
		ast_cli(a->fd, "\nping failed: %s not found\n\n", name);
		return CLI_SUCCESS;
	}
	ast_cli(a->fd, "\npinging %s ...", name);
	when = ast_tvadd((begin = ast_tvnow()), ast_samp2tv(1000, 1000));
	ts.tv_sec = when.tv_sec;
	ts.tv_nsec = when.tv_usec * 1000;
	ast_mutex_lock(&cli_ping_cond_lock);
	if (ast_taskprocessor_push(tps, tps_ping_handler, 0) < 0) {
		ast_cli(a->fd, "\nping failed: could not push task to %s\n\n", name);
		ao2_ref(tps, -1);
		return CLI_FAILURE;
	}
	ast_cond_timedwait(&cli_ping_cond, &cli_ping_cond_lock, &ts);
	ast_mutex_unlock(&cli_ping_cond_lock);
	end = ast_tvnow();
	delta = ast_tvsub(end, begin);
	ast_cli(a->fd, "\n\t%24s ping time: %.1ld.%.6ld sec\n\n", name, (long)delta.tv_sec, (long int)delta.tv_usec);
	ao2_ref(tps, -1);
	return CLI_SUCCESS;
}
