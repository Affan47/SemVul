bignum_digit_to_bignum(bignum_digit_type digit, int negative_p)
{
	if (digit == 0)
		return (BIGNUM_ZERO ());
	else
	{
		bignum * result = (allot_bignum (1, negative_p));
		(BIGNUM_REF (result, 0)) = digit;
		return (result);
	}
}
