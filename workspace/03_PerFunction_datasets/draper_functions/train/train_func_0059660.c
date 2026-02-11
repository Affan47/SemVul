update_interrupts(void)
{
	int gen_int;


	gen_int  = irq_state[0] & irq_enable[0];
	gen_int |= irq_state[1] & irq_enable[1];
	gen_int |= irq_state[2] & irq_enable[2];
	gen_int  = gen_int ? ASSERT_LINE : CLEAR_LINE;


	if (irq_line_state != gen_int)
	{
		irq_line_state = gen_int;
		if (irq_line_state != CLEAR_LINE)
			cpu_set_irq_line(0, ASAP_IRQ0, irq_line_state);
		else
			asap_set_irq_line(ASAP_IRQ0, irq_line_state);
	}
}
