isl_aff_ceil(__isl_take isl_aff *aff)
{
	if (!aff)
		return NULL;

	if (isl_int_is_one(aff->v->el[0]))
		return aff;

	aff = isl_aff_cow(aff);
	if (!aff)
		return NULL;
	aff->v = isl_vec_cow(aff->v);
	if (!aff->v)
		return isl_aff_free(aff);

	isl_int_add(aff->v->el[1], aff->v->el[1], aff->v->el[0]);
	isl_int_sub_ui(aff->v->el[1], aff->v->el[1], 1);
	aff = isl_aff_floor(aff);

	return aff;
}
