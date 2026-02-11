cob_intr_standard_deviation (const int params, ...)
{
	cob_field	*f;
	va_list		args;
	int		i;

	va_start (args, params);
	make_double_entry ();

	if (params == 1) {
		va_end (args);
		cob_set_int (curr_field, 0);
		return curr_field;
	}


	mpz_set_ui (d1.value, 0);
	d1.scale = 0;

	for (i = 0; i < params; ++i) {
		f = va_arg (args, cob_field *);
		cob_decimal_set_field (&d2, f);
		cob_decimal_add (&d1, &d2);
	}
	va_end (args);
	mpz_set_ui (d2.value, (unsigned int)params);
	d2.scale = 0;
	cob_decimal_div (&d1, &d2);


	mpz_set_ui (d4.value, 0);
	d4.scale = 0;

	va_start (args, params);

	for (i = 0; i < params; ++i) {
		f = va_arg (args, cob_field *);
		cob_decimal_set_field (&d2, f);
		cob_decimal_sub (&d2, &d1);
		cob_decimal_mul (&d2, &d2);
		cob_decimal_add (&d4, &d2);
	}
	va_end (args);

	mpz_set_ui (d3.value, (unsigned int)params);
	d3.scale = 0;
	cob_decimal_div (&d4, &d3);


	cob_decimal_get_field (&d4, curr_field, 0);
	f = cob_intr_sqrt (curr_field);
	return f;
}
