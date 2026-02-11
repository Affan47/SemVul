g65816_reset(void* param)
{

		CPU_STOPPED = 0;


		REGISTER_D = 0;
		REGISTER_PB = 0;
		REGISTER_DB = 0;
		REGISTER_S = (REGISTER_S & 0xff) | 0x100;
		REGISTER_X &= 0xff;
		REGISTER_Y &= 0xff;
		if(!FLAG_M)
		{
			REGISTER_B = REGISTER_A & 0xff00;
			REGISTER_A &= 0xff;
		}
		FLAG_E = EFLAG_SET;
		FLAG_M = MFLAG_SET;
		FLAG_X = XFLAG_SET;


		FLAG_D = DFLAG_CLEAR;
		FLAG_I = IFLAG_SET;


		LINE_IRQ = 0;
		LINE_NMI = 0;
		IRQ_DELAY = 0;


		g65816i_set_execution_mode(EXECUTION_MODE_E);


		FLAG_Z = ZFLAG_CLEAR;
		REGISTER_S = 0x1ff;


		REGISTER_PC = g65816_read_8(VECTOR_RESET) | (g65816_read_8(VECTOR_RESET+1)<<8);
		g65816i_jumping(REGISTER_PB | REGISTER_PC);
}
