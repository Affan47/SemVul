isl_val_free(__isl_take isl_val *v)
{
	if (!v)
		return NULL;

	if (--v->ref > 0)
		return NULL;

	isl_ctx_deref(v->ctx);
	isl_int_clear(v->n);
	isl_int_clear(v->d);
	free(v);
	return NULL;
}
