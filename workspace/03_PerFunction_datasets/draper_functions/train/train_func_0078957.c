isl_aff_plain_is_equal(__isl_keep isl_aff *aff1, __isl_keep isl_aff *aff2)
{
	int equal;

	if (!aff1 || !aff2)
		return -1;

	if (isl_aff_is_nan(aff1) || isl_aff_is_nan(aff2))
		return 0;

	equal = isl_local_space_is_equal(aff1->ls, aff2->ls);
	if (equal < 0 || !equal)
		return equal;

	return isl_vec_is_equal(aff1->v, aff2->v);
}
