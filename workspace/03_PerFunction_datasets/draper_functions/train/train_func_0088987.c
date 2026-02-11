e132xs_mask(void)
{
	INT32 val, const_val;

	if( S_BIT )
	{
		val = GET_L_REG(S_CODE);
	}
	else
	{
		val = GET_G_REG(S_CODE);
	}

	const_val = get_const();

	val &= const_val;

	SET_RD(val, NOINC);

	SET_Z((val == 0 ? 1: 0));

	e132xs_ICount -= 1;
}
