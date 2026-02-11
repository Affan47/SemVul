compare_gnumeric_eigen_ev (const void *a, const void *b)
{
	const gnumeric_eigen_ev_t *da = a;
	const gnumeric_eigen_ev_t *db = b;
	gnm_float ea = da->val;
	gnm_float eb = db->val;


	if (gnm_abs (ea) > gnm_abs (eb))
		return -1;
	else if (gnm_abs (ea) < gnm_abs (eb))
		return +1;


	if (ea > eb)
		return -1;
	else if (ea < eb)
		return +1;
	else
		return 0;
}
