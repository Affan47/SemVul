z8000_reset(void *param)
{
	memset(&Z, 0, sizeof(z8000_Regs));
	FCW = RDMEM_W( 2 );
	PC	= RDMEM_W( 4 );
	change_pc16bew(PC);
}
