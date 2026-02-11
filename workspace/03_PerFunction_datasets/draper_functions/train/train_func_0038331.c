m65c02_execute(int cycles)
{
	m6502_ICount = cycles;

	change_pc16(PCD);

	do
	{
		UINT8 op;
		PPC = PCD;

		CALL_MAME_DEBUG;

		op = RDOP();
		(*m6502.insn[op])();


		if( m6502.pending_irq )
			m65c02_take_irq();


		if( m6502.after_cli )
		{
			LOG(("M6502#%d after_cli was >0", cpu_getactivecpu()));
			m6502.after_cli = 0;
			if (m6502.irq_state != CLEAR_LINE)
			{
				LOG((": irq line is asserted: set pending IRQ\n"));
				m6502.pending_irq = 1;
			}
			else
			{
				LOG((": irq line is clear\n"));
			}
		}
		else
		if( m6502.pending_irq )
			m65c02_take_irq();

	} while (m6502_ICount > 0);

	return cycles - m6502_ICount;
}
