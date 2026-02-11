konami_set_irq_line(int irqline, int state)
{
	if (irqline == IRQ_LINE_NMI)
	{
		if (konami.nmi_state == state) return;
		konami.nmi_state = state;
		LOG(("KONAMI#%d set_nmi_line %d\n", cpu_getactivecpu(), state));
		if( state == CLEAR_LINE ) return;


	    if( !(konami.int_state & KONAMI_LDS) ) return;

	    konami.int_state &= ~KONAMI_SYNC;

		if( konami.int_state & KONAMI_CWAI )
		{
			konami.int_state &= ~KONAMI_CWAI;
			konami.extra_cycles += 7;
	    }
		else
		{
			CC |= CC_E;
			PUSHWORD(pPC);
			PUSHWORD(pU);
			PUSHWORD(pY);
			PUSHWORD(pX);
			PUSHBYTE(DP);
			PUSHBYTE(B);
			PUSHBYTE(A);
			PUSHBYTE(CC);
			konami.extra_cycles += 19;
		}
		CC |= CC_IF | CC_II;
		PCD = RM16(0xfffc);
		change_pc16(PC);
	}
	else if (irqline < 2)
	{
	    LOG(("KONAMI#%d set_irq_line %d, %d\n", cpu_getactivecpu(), irqline, state));
		konami.irq_state[irqline] = state;
		if (state == CLEAR_LINE) return;
		CHECK_IRQ_LINES;
	}
}
