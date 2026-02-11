m6502_set_irq_line(int irqline, int state)
{
	if (irqline == IRQ_LINE_NMI)
	{
		if (m6502.nmi_state == state) return;
		m6502.nmi_state = state;
		if( state != CLEAR_LINE )
		{
			LOG(( "M6502#%d set_nmi_line(ASSERT)\n", cpu_getactivecpu()));
			EAD = M6502_NMI_VEC;
			m6502_ICount -= 7;
			PUSH(PCH);
			PUSH(PCL);
			PUSH(P & ~F_B);
			P |= F_I;
			PCL = RDMEM(EAD);
			PCH = RDMEM(EAD+1);
			LOG(("M6502#%d takes NMI ($%04x)\n", cpu_getactivecpu(), PCD));
			change_pc16(PCD);
		}
	}
	else
	{
		if( irqline == M6502_SET_OVERFLOW )
		{
			if( m6502.so_state && !state )
			{
				LOG(( "M6502#%d set overflow\n", cpu_getactivecpu()));
				P|=F_V;
			}
			m6502.so_state=state;
			return;
		}
		m6502.irq_state = state;
		if( state != CLEAR_LINE )
		{
			LOG(( "M6502#%d set_irq_line(ASSERT)\n", cpu_getactivecpu()));
			m6502.pending_irq = 1;
		}
	}
}
