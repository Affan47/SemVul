m68k_op_jmp_32_pcdi(void)
{
	m68ki_jump(EA_PCDI_32());
	m68ki_trace_t0();
	if(REG_PC == REG_PPC)
		USE_ALL_CYCLES();
}
