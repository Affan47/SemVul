isl_val_dup(__isl_keep isl_val *val)
{
	isl_val *dup;

	if (!val)
		return NULL;

	dup = isl_val_alloc(isl_val_get_ctx(val));
	if (!dup)
		return NULL;

	isl_int_set(dup->n, val->n);
	isl_int_set(dup->d, val->d);

	return dup;
}
