jtf_i(void)
{
	UINT8 adr = ROP_ARG(PC);
	PC += 1;
	if( CONTROL & TOVF )
		PC = (PC & 0x700) | adr;
	CONTROL &= ~TOVF;
}
