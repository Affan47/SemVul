e132xs_sard(void)
{
	INT32 low_order, high_order;
	INT64 val;
	unsigned int n = OP & 0x1f;
	int sign_bit;


	if( S_CODE != D_CODE && S_CODE != (D_CODE + INC) )
	{
		high_order = GET_L_REG(D_CODE);
		low_order = GET_L_REG(D_CODE + INC);

		val = (INT64) COMBINE_64_32_32(high_order, low_order);
		sign_bit = (val & 0x8000000000000000) >> 63;

		val >>= n;

		if( sign_bit )
		{
			int i;
			for( i = 0; i < n; i++ )
			{
				val |= (0x8000000000000000 >> i);
			}
		}

		high_order = (val & 0xffffffff00000000) >> 32;
		low_order = val & 0x00000000ffffffff;

		SET_RD(high_order, NOINC);
		SET_RD(low_order, INC);
		SET_Z((val == 0 ? 1: 0));
		SET_N(SIGN_BIT(high_order));

	}

	e132xs_ICount -= 2;
}
