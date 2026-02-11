lb_bpf_func_get(struct team *team, struct team_gsetter_ctx *ctx)
{
	struct lb_priv *lb_priv = get_lb_priv(team);

	if (!lb_priv->ex->orig_fprog) {
		ctx->data.bin_val.len = 0;
		ctx->data.bin_val.ptr = NULL;
		return 0;
	}
	ctx->data.bin_val.len = lb_priv->ex->orig_fprog->len *
				sizeof(struct sock_filter);
	ctx->data.bin_val.ptr = lb_priv->ex->orig_fprog->filter;
	return 0;
}
