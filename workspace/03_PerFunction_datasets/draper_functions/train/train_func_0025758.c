generate_exception(int exception, int backup)
{


	if (backup)
		mips3.pc = mips3.ppc;


	mips3.cpr[0][COP0_EPC] = mips3.pc;


	CAUSE = (CAUSE & ~0x800000ff) | (exception << 2);


	if (mips3.nextpc != ~0)
	{
		mips3.nextpc = ~0;
		mips3.cpr[0][COP0_EPC] -= 4;
		CAUSE |= 0x80000000;
	}


	SR |= SR_EXL;


	mips3.pc = (SR & SR_BEV) ? 0xbfc00200 : 0x80000000;


	if (exception >= EXCEPTION_TLBMOD && exception <= EXCEPTION_TLBSTORE)
		mips3.pc += 0x80;
	else
		mips3.pc += 0x180;


	if (mips3.bigendian)
		change_pc32bedw(mips3.pc);
	else
		change_pc32ledw(mips3.pc);
}
