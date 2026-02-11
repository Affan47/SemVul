cli_bcapi_ilog2(struct cli_bc_ctx *ctx, uint32_t a, uint32_t b)
{
    double f;
    if (!b)
	return 0x7fffffff;

    f = (1<<26)*log((double)a / b) / log(2);
    return (int32_t)myround(f);
}
