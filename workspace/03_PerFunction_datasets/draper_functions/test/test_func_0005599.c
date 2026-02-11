test_residue_class(isl_ctx *ctx)
{
	const char *str;
	isl_set *set;
	isl_int m, r;
	int res;

	str = "{ [i,j] : j = 4 i + 1 and 0 <= i <= 100; "
		"[i,j] : j = 4 i + 3 and 500 <= i <= 600 }";
	set = isl_set_read_from_str(ctx, str);
	isl_int_init(m);
	isl_int_init(r);
	res = isl_set_dim_residue_class(set, 1, &m, &r);
	if (res >= 0 &&
	    (isl_int_cmp_si(m, 2) != 0 || isl_int_cmp_si(r, 1) != 0))
		isl_die(ctx, isl_error_unknown, "incorrect residue class",
			res = -1);
	isl_int_clear(r);
	isl_int_clear(m);
	isl_set_free(set);

	return res;
}
