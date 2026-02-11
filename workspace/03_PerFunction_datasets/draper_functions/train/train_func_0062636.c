tms32010_execute(int cycles)
{
	tms32010_icount = cycles;

	do
	{
		if (R.INTF) {

			if ((R.opcode.b.h != 0x6d) && ((R.opcode.b.h & 0xe0) != 0x80) && (R.opcode.w.l != 0x7f82))
				tms32010_icount -= Ext_IRQ();
		}

		R.PREVPC = R.PC;

		CALL_MAME_DEBUG;

		R.opcode.d = M_RDOP(R.PC);
		R.PC++;

		if (R.opcode.b.h != 0x7f)	{
			tms32010_icount -= cycles_main[R.opcode.b.h];
			(*(opcode_main[R.opcode.b.h]))();
		}
		else {
			tms32010_icount -= cycles_7F_other[(R.opcode.b.l & 0x1f)];
			(*(opcode_7F_other[(R.opcode.b.l & 0x1f)]))();
		}
	} while (tms32010_icount>0);

	return cycles - tms32010_icount;
}
