isl_upoly_add_isl_int(
	__isl_take struct isl_upoly *up, isl_int v)
{
	struct isl_upoly_rec *rec;

	if (!up)
		return NULL;

	if (isl_upoly_is_cst(up))
		return isl_upoly_cst_add_isl_int(up, v);

	up = isl_upoly_cow(up);
	rec = isl_upoly_as_rec(up);
	if (!rec)
		goto error;

	rec->p[0] = isl_upoly_add_isl_int(rec->p[0], v);
	if (!rec->p[0])
		goto error;

	return up;
error:
	isl_upoly_free(up);
	return NULL;
}
