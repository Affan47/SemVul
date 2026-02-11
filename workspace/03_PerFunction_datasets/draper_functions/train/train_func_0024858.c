icx_set_token_processor(Icx_ctx *ctx, Icx_token_processing_func processor)
{

  if (processor == NULL)
	ctx->processor = icx_saml11_process_token;
  else
	ctx->processor = processor;
}
