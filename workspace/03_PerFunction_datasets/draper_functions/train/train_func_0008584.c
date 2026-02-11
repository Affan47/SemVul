aff_nonneg_basic_set(
	__isl_take isl_aff *aff, int rational)
{
	isl_constraint *ineq;
	isl_basic_set *bset;

	ineq = isl_inequality_from_aff(aff);

	bset = isl_basic_set_from_constraint(ineq);
	if (rational)
		bset = isl_basic_set_set_rational(bset);
	bset = isl_basic_set_simplify(bset);
	return bset;
}
