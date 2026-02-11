cli_scanriff(cli_ctx *ctx)
{
	int ret = CL_CLEAN;

    if(cli_check_riff_exploit(ctx) == 2) {
	ret = CL_VIRUS;
	cli_append_virus(ctx, "Heuristics.Exploit.W32.MS05-002");
    }

    return ret;
}
