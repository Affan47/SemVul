mcf_banner(struct cli *cli, const char *const *av, void *priv)
{

	(void)av;
	(void)priv;
	VCLI_Out(cli, "-----------------------------\n");
	VCLI_Out(cli, "Varnish Cache CLI 1.0\n");
	VCLI_Out(cli, "-----------------------------\n");
	VCLI_Out(cli, "%s\n", VSB_data(vident) + 1);
	VCLI_Out(cli, "\n");
	VCLI_Out(cli, "Type 'help' for command list.\n");
	VCLI_Out(cli, "Type 'quit' to close CLI session.\n");
	if (child_pid < 0)
		VCLI_Out(cli, "Type 'start' to launch worker process.\n");
	VCLI_SetResult(cli, CLIS_OK);
}
