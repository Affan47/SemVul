parse_data_for_row_truecolor(TGAContext *ctx)
{
	g_memmove(ctx->pptr, ctx->in->data, ctx->pbuf->rowstride);
	swap_channels(ctx);
}
