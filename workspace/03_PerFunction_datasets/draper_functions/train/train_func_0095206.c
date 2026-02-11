add_mod(size_t length, u_int8_t a[], u_int8_t b[], u_int8_t sum[])
{
	int i, c = 0;

	for(i = length - 1; i >= 0; i--)
	{
		u_int32_t tmp;

		tmp = a[i] + b[i] + c;
		sum[i] = 0xff & tmp;
		c = tmp >> 8;
	}
}
