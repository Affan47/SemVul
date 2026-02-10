icx_add_audience(Icx_ctx *ctx, char *audience)
{

  if (ctx->audience == NULL)
	ctx->audience = dsvec_init(NULL, sizeof(char *));


  dsvec_add_ptr(ctx->audience, strdup(audience));

  return(0);
}
