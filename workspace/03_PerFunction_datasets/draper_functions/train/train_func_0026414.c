gda_meta_context_copy (GdaMetaContext *ctx)
{
	g_return_val_if_fail (ctx, NULL);

	GdaMetaContext *n;
	n = gda_meta_context_new ();
	gda_meta_context_set_table (n, gda_meta_context_get_table (ctx));
	gda_meta_context_set_columns (n, ctx->columns, NULL);

	return n;
}
