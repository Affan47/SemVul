m68k_op_chk_16_d(void)
{
	sint src = MAKE_INT_16(DX);
	sint bound = MAKE_INT_16(DY);

	FLAG_Z = ZFLAG_16(src);
	FLAG_V = VFLAG_CLEAR;
	FLAG_C = CFLAG_CLEAR;

	if(src >= 0 && src <= bound)
	{
		return;
	}
	FLAG_N = (src < 0)<<7;
	m68ki_exception_trap(EXCEPTION_CHK);
}
