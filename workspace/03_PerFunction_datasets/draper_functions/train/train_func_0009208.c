m68k_op_tst_8_i(void)
{
	if(CPU_TYPE_IS_EC020_PLUS(CPU_TYPE))
	{
		uint res = OPER_I_8();

		FLAG_N = NFLAG_8(res);
		FLAG_Z = res;
		FLAG_V = VFLAG_CLEAR;
		FLAG_C = CFLAG_CLEAR;
		return;
	}
	m68ki_exception_illegal();
}
