cli_release_handler(struct stream_interface *si)
{
	struct appctx *appctx = __objt_appctx(si->end);

	if (appctx->st0 == STAT_CLI_O_SESS && appctx->st2 == STAT_ST_LIST) {
		if (!LIST_ISEMPTY(&appctx->ctx.sess.bref.users))
			LIST_DEL(&appctx->ctx.sess.bref.users);
	}
	else if (appctx->st0 == STAT_CLI_PRINT_FREE) {
		free(appctx->ctx.cli.err);
	}
	else if (appctx->st0 == STAT_CLI_O_MLOOK) {
		free(appctx->ctx.map.chunk.str);
	}
}
