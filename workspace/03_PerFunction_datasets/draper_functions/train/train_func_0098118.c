X509_LOOKUP_by_subject(X509_LOOKUP *ctx, int type, X509_NAME *name,
	     X509_OBJECT *ret)
	{
	if ((ctx->method == NULL) || (ctx->method->get_by_subject == NULL))
		return X509_LU_FAIL;
	if (ctx->skip) return 0;
	return ctx->method->get_by_subject(ctx,type,name,ret);
	}
