bls(void)
{
	if (asap.znflag == 0 || !asap.cflag)
	{
		asap.nextpc = asap.ppc + ((INT32)(asap.op.d << 10) >> 8);

		fetch_instruction();
		asap.pc = asap.nextpc;
		asap.nextpc = ~0;


		execute_instruction();
		asap_icount--;
	}
}
