hd63705_set_irq_line(int irqline, int state)
{
	if (irqline == IRQ_LINE_NMI)
	{
		if (m6805.nmi_state == state) return;

		m6805.nmi_state = state;
		if (state != CLEAR_LINE)
			m6805.pending_interrupts |= 1<<HD63705_INT_NMI;
	}
	else if (irqline <= HD63705_INT_ADCONV)
	{
		if (m6805.irq_state[irqline] == state) return;
		m6805.irq_state[irqline] = state;
		if (state != CLEAR_LINE) m6805.pending_interrupts |= 1<<irqline;
	}
}
