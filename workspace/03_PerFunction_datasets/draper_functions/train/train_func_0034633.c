e132xs_stdp(void)
{
	UINT32 val_high, val_low;

	if( S_BIT )
	{
		val_high = GET_L_REG(S_CODE);
		val_low  = GET_L_REG(S_CODE + INC);
	}
	else
	{
		val_high = GET_G_REG(S_CODE);
		val_low  = GET_G_REG(S_CODE + INC);
	}

	WRITE_W( GET_L_REG(D_CODE), val_high );
	WRITE_W( GET_L_REG(D_CODE) + 4, val_low );
	SET_L_REG( D_CODE, GET_L_REG(D_CODE) + 8 );

	e132xs_ICount -= 2;
}
