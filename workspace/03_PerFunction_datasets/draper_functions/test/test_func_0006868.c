VCLI_Quote(struct cli *cli, const char *s)
{

	CHECK_OBJ_NOTNULL(cli, CLI_MAGIC);
	VSB_quote(cli->sb, s, -1, 0);
}
