e132xs_movd(void)
{

	if( D_CODE == PC_CODE && !D_BIT )
	{


		unsigned char old_s, old_l;
		UINT8 difference;

		if( (S_CODE == PC_CODE && !S_BIT) || (S_CODE == SR_CODE && !S_BIT) )
		{
			verboselog( 1, "Denoted PC or SR used in RET instruction @ %x\n", PC );
		}
		else
		{
			old_s = GET_S;
			old_l = GET_L;
			PPC = PC;

			if( S_BIT )
			{
				PC = GET_L_REG(S_CODE) & 0xfffffffe;
				SR = (GET_L_REG(S_CODE + INC) & 0xffe00000) | ((GET_L_REG(S_CODE) & 0x01) << 18 ) | (GET_L_REG(S_CODE + INC) & 0x3ffff);
				SET_S(GET_L_REG(S_CODE) & 0x01);
			}
			else
			{
				PC = GET_G_REG(S_CODE) & 0xfffffffe;
				SR = (GET_G_REG(S_CODE + INC) & 0xffe00000) | ((GET_G_REG(S_CODE) & 0x01) << 18 ) | (GET_G_REG(S_CODE + INC) & 0x3ffff);
				SET_S(GET_G_REG(S_CODE) & 0x01);
			}

			SET_ILC(0);

			if( (!old_s && GET_S) || (!GET_S && !old_l && GET_L))
			{
				UINT32 addr = get_trap_addr(PRIVILEGE_ERROR);
				execute_trap(addr);
			}

			difference = GET_FP - ( ( SP & 0x1fc ) >> 2 );


			if( difference & 0x40 )
			{
				do
				{
					SP -= 4;

					SET_L_REG( ( SP & 0xfc ), READ_W( SP ) );

					difference++;
					difference = ((difference & 0x7f) + ((difference & 0x80) >> 7)) & 0x7f;

				} while( !( difference & 0x40 ) );
			}
		}


		e132xs_ICount -= 1;
	}

	else if( S_CODE == SR_CODE && !S_BIT )
	{
		SET_RD(0, NOINC);
		SET_RD(0, INC);
		SET_Z(1);
		SET_N(0);


		e132xs_ICount -= 2;
	}

	else
	{
		UINT32 val1, val2;
		UINT64 tmp;

		if( S_BIT )
		{
			val1 = GET_L_REG(S_CODE);
			val2 = GET_L_REG(S_CODE + INC);
		}
		else
		{
			val1 = GET_G_REG(S_CODE);
			val2 = GET_G_REG(S_CODE + INC);
		}

		SET_RD(val1, NOINC);
		SET_RD(val2, INC);
		tmp = COMBINE_U64_U32_U32(val1, val2);
		SET_Z(tmp == 0 ? 1 : 0);
		SET_N(SIGN_BIT(val1));


		e132xs_ICount -= 2;
	}
}
