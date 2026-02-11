cli_mbox(const char *dir, cli_ctx *ctx)
{
	if(dir == NULL) {
		cli_dbgmsg("cli_mbox called with NULL dir\n");
		return CL_ENULLARG;
	}
	return cli_parse_mbox(dir, ctx);
}
