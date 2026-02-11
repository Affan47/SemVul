update_mcr68_interrupts(void)
{
	int newstate = 0;


	if (v493_irq_state)
		newstate = v493_irq_vector;
	if (m6840_irq_state)
		newstate = m6840_irq_vector;


	if (newstate)
		cpu_set_irq_line(0, newstate, ASSERT_LINE);
	else
		cpu_set_irq_line(0, 7, CLEAR_LINE);
}
