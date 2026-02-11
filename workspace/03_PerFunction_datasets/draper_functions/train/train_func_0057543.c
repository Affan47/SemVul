m68010_get_reg(int regnum)
{
	switch( regnum )
	{
		case M68K_VBR: return m68k_get_reg(NULL, M68K_REG_VBR);
		case M68K_SFC: return m68k_get_reg(NULL, M68K_REG_SFC);
		case M68K_DFC: return m68k_get_reg(NULL, M68K_REG_DFC);
		case REG_PC:   return m68k_get_reg(NULL, M68K_REG_PC)&0x00ffffff;
		case M68K_PC:  return m68k_get_reg(NULL, M68K_REG_PC);
		case REG_SP:
		case M68K_SP:  return m68k_get_reg(NULL, M68K_REG_SP);
		case M68K_ISP: return m68k_get_reg(NULL, M68K_REG_ISP);
		case M68K_USP: return m68k_get_reg(NULL, M68K_REG_USP);
		case M68K_SR:  return m68k_get_reg(NULL, M68K_REG_SR);
		case M68K_D0:  return m68k_get_reg(NULL, M68K_REG_D0);
		case M68K_D1:  return m68k_get_reg(NULL, M68K_REG_D1);
		case M68K_D2:  return m68k_get_reg(NULL, M68K_REG_D2);
		case M68K_D3:  return m68k_get_reg(NULL, M68K_REG_D3);
		case M68K_D4:  return m68k_get_reg(NULL, M68K_REG_D4);
		case M68K_D5:  return m68k_get_reg(NULL, M68K_REG_D5);
		case M68K_D6:  return m68k_get_reg(NULL, M68K_REG_D6);
		case M68K_D7:  return m68k_get_reg(NULL, M68K_REG_D7);
		case M68K_A0:  return m68k_get_reg(NULL, M68K_REG_A0);
		case M68K_A1:  return m68k_get_reg(NULL, M68K_REG_A1);
		case M68K_A2:  return m68k_get_reg(NULL, M68K_REG_A2);
		case M68K_A3:  return m68k_get_reg(NULL, M68K_REG_A3);
		case M68K_A4:  return m68k_get_reg(NULL, M68K_REG_A4);
		case M68K_A5:  return m68k_get_reg(NULL, M68K_REG_A5);
		case M68K_A6:  return m68k_get_reg(NULL, M68K_REG_A6);
		case M68K_A7:  return m68k_get_reg(NULL, M68K_REG_A7);
		case M68K_PREF_ADDR:  return m68k_get_reg(NULL, M68K_REG_PREF_ADDR);
		case M68K_PREF_DATA:  return m68k_get_reg(NULL, M68K_REG_PREF_DATA);
		case REG_PREVIOUSPC: return m68k_get_reg(NULL, M68K_REG_PPC);

		default:
			if( regnum < REG_SP_CONTENTS )
			{
				unsigned offset = m68k_get_reg(NULL, M68K_REG_SP) + 4 * (REG_SP_CONTENTS - regnum);
				if( offset < 0xfffffd )
					return m68k_read_memory_32( offset );
			}
	}
	return 0;
}
