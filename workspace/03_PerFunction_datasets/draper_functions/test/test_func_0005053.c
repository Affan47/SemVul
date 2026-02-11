e132xs_call(void)
{
	INT32 const_val;


	const_val = get_const();

	verboselog( 0, "Immediate value for CALL: %04x\n", const_val );

	if( !(S_CODE == SR_CODE && !S_BIT) )
	{
		if( S_BIT )
		{
			const_val += GET_L_REG(S_CODE);
		}
		else
		{
			const_val += GET_G_REG(S_CODE);
		}
	}

	SET_LD(((PC & 0xfffffffe) | GET_S), NOINC);
	SET_LD(SR, INC);

	if( D_CODE )
		SET_FP((GET_FP + D_CODE));
	else
		SET_FP((GET_FP + 16));

	SET_FL(6);
	SET_M(0);

	PPC = PC;
	PC = const_val;


	e132xs_ICount -= 1;
}
