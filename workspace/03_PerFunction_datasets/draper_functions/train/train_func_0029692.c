row_mysql_read_true_varchar(

	ulint*		len,
	const byte*	field,
	ulint		lenlen)

{
	if (lenlen == 2) {
		*len = mach_read_from_2_little_endian(field);

		return(field + 2);
	}

	ut_a(lenlen == 1);

	*len = mach_read_from_1(field);

	return(field + 1);
}
