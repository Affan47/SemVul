e132xs_stwr(void)
{
	UINT32 val;

	if( S_BIT )
	{
		val = GET_L_REG(S_CODE);
	}
	else
	{
		val = GET_G_REG(S_CODE);
	}

	WRITE_W( GET_L_REG(D_CODE), val );

	e132xs_ICount -= 1;
}
