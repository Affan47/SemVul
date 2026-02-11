jaguargpu_set_irq_line(int irqline, int state)
{
	int mask = 0x40 << irqline;
	jaguar.ctrl[G_CTRL] &= ~mask;
	if (state != CLEAR_LINE)
	{
		jaguar.ctrl[G_CTRL] |= mask;
		check_irqs();
	}
}
