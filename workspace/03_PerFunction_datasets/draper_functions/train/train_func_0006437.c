url_adapt_ext(const char *src, size_t srclen, size_t *newlen, zend_bool do_flush TSRMLS_DC)
{
	url_adapt_state_ex_t *ctx;
	char *retval;

	ctx = &BG(url_adapt_state_ex);

	xx_mainloop(ctx, src, srclen TSRMLS_CC);

	*newlen = ctx->result.len;
	if (!ctx->result.c) {
		smart_str_appendl(&ctx->result, "", 0);
	}
	smart_str_0(&ctx->result);
	if (do_flush) {
		smart_str_appendl(&ctx->result, ctx->buf.c, ctx->buf.len);
		*newlen += ctx->buf.len;
		smart_str_free(&ctx->buf);
	}
	retval = ctx->result.c;
	ctx->result.c = NULL;
	ctx->result.len = 0;
	return retval;
}
