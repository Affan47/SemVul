BRA(UINT32 d)
{
	INT32 disp = ((INT32)d << 20) >> 20;

#if BUSY_LOOP_HACKS
	if (disp == -2)
	{
		UINT32 next_opcode = RW(sh2.ppc & AM);


		if (next_opcode == 0x0009)
			sh2_icount %= 3;
	}
#endif
	sh2.delay = sh2.pc;
	sh2.pc = sh2.ea = sh2.pc + disp * 2 + 2;
	sh2_icount--;
}
