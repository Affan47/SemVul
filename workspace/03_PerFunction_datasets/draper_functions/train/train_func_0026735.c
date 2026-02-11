isl_int_obj_alloc(isl_ctx *ctx, isl_int v)
{
	isl_int_obj *i;

	i = isl_alloc_type(ctx, isl_int_obj);
	if (!i)
		return NULL;

	i->ctx = ctx;
	isl_ctx_ref(ctx);
	i->ref = 1;
	isl_int_init(i->v);
	isl_int_set(i->v, v);

	return i;
}
