console_transfer(struct ast_cli_entry *e, int cmd, struct ast_cli_args *a)
{
	struct chan_oss_pvt *o = find_desc(oss_active);
	struct ast_channel *b = NULL;
	char *tmp, *ext, *ctx;

	switch (cmd) {
	case CLI_INIT:
		e->command = "console transfer";
		e->usage =
			"Usage: console transfer <extension>[@context]\n"
			"       Transfers the currently connected call to the given extension (and\n"
			"       context if specified)\n";
		return NULL;
	case CLI_GENERATE:
		return NULL;
	}

	if (a->argc != 3)
		return CLI_SHOWUSAGE;
	if (o == NULL)
		return CLI_FAILURE;
	if (o->owner == NULL || (b = ast_bridged_channel(o->owner)) == NULL) {
		ast_cli(a->fd, "There is no call to transfer\n");
		return CLI_SUCCESS;
	}

	tmp = ast_ext_ctx(a->argv[2], &ext, &ctx);
	if (ctx == NULL)
		ctx = ast_strdupa(ast_channel_context(o->owner));
	if (!ast_exists_extension(b, ctx, ext, 1,
		S_COR(ast_channel_caller(b)->id.number.valid, ast_channel_caller(b)->id.number.str, NULL))) {
		ast_cli(a->fd, "No such extension exists\n");
	} else {
		ast_cli(a->fd, "Whee, transferring %s to %s@%s.\n", ast_channel_name(b), ext, ctx);
		if (ast_async_goto(b, ctx, ext, 1))
			ast_cli(a->fd, "Failed to transfer :(\n");
	}
	if (tmp)
		ast_free(tmp);
	return CLI_SUCCESS;
}
