isl_restriction_input(
	__isl_take isl_set *source_restr, __isl_take isl_set *sink_restr)
{
	isl_ctx *ctx;
	isl_restriction *restr;

	if (!source_restr || !sink_restr)
		goto error;

	ctx = isl_set_get_ctx(source_restr);
	restr = isl_calloc_type(ctx, struct isl_restriction);
	if (!restr)
		goto error;

	restr->type = isl_restriction_type_input;
	restr->source = source_restr;
	restr->sink = sink_restr;

	return restr;
error:
	isl_set_free(source_restr);
	isl_set_free(sink_restr);
	return NULL;
}
