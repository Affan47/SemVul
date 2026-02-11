cmp_numerics(Numeric num1, Numeric num2)
{
	int			result;


	if (NUMERIC_IS_NAN(num1))
	{
		if (NUMERIC_IS_NAN(num2))
			result = 0;
		else
			result = 1;
	}
	else if (NUMERIC_IS_NAN(num2))
	{
		result = -1;
	}
	else
	{
		result = cmp_var_common(NUMERIC_DIGITS(num1), NUMERIC_NDIGITS(num1),
								num1->n_weight, NUMERIC_SIGN(num1),
								NUMERIC_DIGITS(num2), NUMERIC_NDIGITS(num2),
								num2->n_weight, NUMERIC_SIGN(num2));
	}

	return result;
}
