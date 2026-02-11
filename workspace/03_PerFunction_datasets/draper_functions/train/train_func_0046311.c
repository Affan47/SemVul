cli_scantnef(cli_ctx *ctx)
{
	int ret;
	char *dir = cli_gentemp(ctx->engine->tmpdir);

    if(!dir)
	return CL_EMEM;

    if(mkdir(dir, 0700)) {
	cli_dbgmsg("Can't create temporary directory for tnef file %s\n", dir);
	free(dir);
	return CL_ETMPDIR;
    }

    ret = cli_tnef(dir, ctx);

    if(ret == CL_CLEAN)
	ret = cli_scandir(dir, ctx);

    if(!ctx->engine->keeptmp)
	cli_rmdirs(dir);

    free(dir);
    return ret;
}
