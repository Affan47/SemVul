dtuple_check_typed_no_assert(

	const dtuple_t*	tuple)
{
	const dfield_t*	field;
	ulint		i;

	if (dtuple_get_n_fields(tuple) > REC_MAX_N_FIELDS) {
		fprintf(stderr,
			"InnoDB: Error: index entry has %lu fields\n",
			(ulong) dtuple_get_n_fields(tuple));
dump:
		fputs("InnoDB: Tuple contents: ", stderr);
		dtuple_print(stderr, tuple);
		putc('\n', stderr);

		return(FALSE);
	}

	for (i = 0; i < dtuple_get_n_fields(tuple); i++) {

		field = dtuple_get_nth_field(tuple, i);

		if (!dfield_check_typed_no_assert(field)) {
			goto dump;
		}
	}

	return(TRUE);
}
