pkcs7_sig_note_signature(void *context, size_t hdrlen,
			     unsigned char tag,
			     const void *value, size_t vlen)
{
	struct pkcs7_parse_context *ctx = context;

	BUG_ON(ctx->sinfo->sig.pkey_algo != PKEY_ALGO_RSA);

	ctx->sinfo->sig.s = kmemdup(value, vlen, GFP_KERNEL);
	if (!ctx->sinfo->sig.s)
		return -ENOMEM;

	ctx->sinfo->sig.s_size = vlen;
	return 0;
}
