cob_intr_present_value (const int params, ...)
{
	cob_field	*f;
	va_list		args;
	int		i;

	va_start (args, params);
	make_double_entry ();

	if (params < 2) {
		va_end (args);
		fprintf (stderr, "Wrong number of parameters for FUNCTION PRESENT-VALUE\n");
		fflush (stderr);
		cob_set_int (curr_field, 0);
		return curr_field;
	}
	f = va_arg (args, cob_field *);
	cob_decimal_set_field (&d1, f);
	mpz_set_ui (d2.value, 1);
	d2.scale = 0;
	cob_decimal_add (&d1, &d2);

	mpz_set_ui (d4.value, 0);
	d4.scale = 0;

	for (i = 1; i < params; ++i) {
		f = va_arg (args, cob_field *);
		cob_decimal_set_field (&d2, f);
		mpz_set (d3.value, d1.value);
		d3.scale = d1.scale;
		if (i > 1) {
			mpz_set_ui (d5.value, (unsigned int)i);
			d5.scale = 0;
			cob_decimal_pow (&d3, &d5);
		}
		cob_decimal_div (&d2, &d3);
		cob_decimal_add (&d4, &d2);
	}
	va_end (args);

	cob_decimal_get_field (&d4, curr_field, 0);
	return curr_field;
}
