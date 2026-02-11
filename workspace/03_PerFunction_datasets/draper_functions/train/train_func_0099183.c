prev_realkey(PAGE16 * pagep, indx_t n)
#else
prev_realkey(pagep, n)
	PAGE16 *pagep;
	u_int32_t n;
#endif
{
	int32_t i;


	for (i = n - 1; i > -1; i--)
		if (KEY_OFF(pagep, i) != BIGPAIR)
			return (i);
	return (n);
}
