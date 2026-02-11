gnumeric_imcot (GnmFuncEvalInfo *ei, GnmValue const * const *argv)
{
	complex_t c, res;
	char imunit;

	if (value_get_as_complex (argv[0], &c, &imunit))
		return value_new_error_NUM (ei->pos);

	complex_tan (&res, &c);
	gsl_complex_inverse (&res, &res);
	return value_new_complex (&res, imunit);
}
