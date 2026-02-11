cob_move_binary_to_display (cob_field *f1, cob_field *f2)
{
	int			i, sign;
	unsigned long long	val;
	long long		val2;
	char			buff[64];

	sign = 1;

	if (COB_FIELD_HAVE_SIGN (f1)) {
		val2 = cob_binary_mget_int64 (f1);
		if (val2 < 0) {
			sign = -1;
			val = -val2;
		} else {
			val = val2;
		}
	} else {
		val = cob_binary_mget_int64 (f1);
	}


	i = 20;
	while (val > 0) {
		buff[--i] = (char) cob_i2d (val % 10);
		val /= 10;
	}


	store_common_region (f2, (ucharptr)buff + i, (size_t)(20 - i),
		COB_FIELD_SCALE(f1));

	cob_put_sign (f2, sign);
}
