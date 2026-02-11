isl_reordering_free(__isl_take isl_reordering *exp)
{
	if (!exp)
		return NULL;

	if (--exp->ref > 0)
		return NULL;

	isl_space_free(exp->dim);
	free(exp);
	return NULL;
}
