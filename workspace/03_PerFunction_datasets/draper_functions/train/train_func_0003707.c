allot_bignum_zeroed(bignum_length_type length, int negative_p)
{
	bignum * result = allot_bignum(length,negative_p);
	bignum_digit_type * scan = (BIGNUM_START_PTR (result));
	bignum_digit_type * end = (scan + length);
	while (scan < end)
		(*scan++) = 0;
	return (result);
}
