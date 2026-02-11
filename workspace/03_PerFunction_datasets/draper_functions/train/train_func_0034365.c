dtuple_print(

	FILE*		f,
	const dtuple_t*	tuple)
{
	ulint		n_fields;
	ulint		i;

	n_fields = dtuple_get_n_fields(tuple);

	fprintf(f, "DATA TUPLE: %lu fields;\n", (ulong) n_fields);

	for (i = 0; i < n_fields; i++) {
		fprintf(f, " %lu:", (ulong) i);

		dfield_print_raw(f, dtuple_get_nth_field(tuple, i));

		putc(';', f);
		putc('\n', f);
	}

	ut_ad(dtuple_validate(tuple));
}
