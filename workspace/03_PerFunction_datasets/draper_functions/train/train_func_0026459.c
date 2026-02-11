numeric_out(PG_FUNCTION_ARGS)
{
	Numeric		num = PG_GETARG_NUMERIC(0);
	NumericVar	x;
	char	   *str;


	if (NUMERIC_IS_NAN(num))
		PG_RETURN_CSTRING(pstrdup("NaN"));


	init_var(&x);
	set_var_from_num(num, &x);

	str = get_str_from_var(&x, x.dscale);

	free_var(&x);

	PG_RETURN_CSTRING(str);
}
