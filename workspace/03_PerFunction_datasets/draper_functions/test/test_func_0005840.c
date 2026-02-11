OutputStream_isClosed(CTX ctx, ksfp_t *sfp _RIX)
{
	RETURNb_(io2_isClosed(ctx, (sfp[0].in)->io2));
}
