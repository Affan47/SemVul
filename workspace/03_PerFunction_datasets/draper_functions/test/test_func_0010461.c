isl_aff_scale(__isl_take isl_aff *aff, isl_int f)
{
	isl_int gcd;

	if (!aff)
		return NULL;
	if (isl_aff_is_nan(aff))
		return aff;

	if (isl_int_is_one(f))
		return aff;

	aff = isl_aff_cow(aff);
	if (!aff)
		return NULL;
	aff->v = isl_vec_cow(aff->v);
	if (!aff->v)
		return isl_aff_free(aff);

	if (isl_int_is_pos(f) && isl_int_is_divisible_by(aff->v->el[0], f)) {
		isl_int_divexact(aff->v->el[0], aff->v->el[0], f);
		return aff;
	}

	isl_int_init(gcd);
	isl_int_gcd(gcd, aff->v->el[0], f);
	isl_int_divexact(aff->v->el[0], aff->v->el[0], gcd);
	isl_int_divexact(gcd, f, gcd);
	isl_seq_scale(aff->v->el + 1, aff->v->el + 1, gcd, aff->v->size - 1);
	isl_int_clear(gcd);

	return aff;
}
