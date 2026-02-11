e132xs_shli(void)
{
	UINT32 val;

	if( D_BIT )
	{
		val = GET_L_REG(D_CODE);
	}
	else
	{
		val = GET_G_REG(D_CODE);
	}

	val <<= N_VALUE;
	SET_RD(val, NOINC);
	SET_Z((val == 0 ? 1: 0));
	SET_N(SIGN_BIT(val));


	e132xs_ICount -= 1;
}
