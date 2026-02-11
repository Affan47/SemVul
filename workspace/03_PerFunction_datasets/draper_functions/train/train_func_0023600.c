mod_var(NumericVar *var1, NumericVar *var2, NumericVar *result)
{
	NumericVar	tmp;

	init_var(&tmp);


	div_var(var1, var2, &tmp, 0, false);

	mul_var(var2, &tmp, &tmp, var2->dscale);

	sub_var(var1, &tmp, result);

	free_var(&tmp);
}
