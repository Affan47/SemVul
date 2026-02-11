write_snd_020(int reg, int val)
{
	sndto000[reg] = val;

	if (reg == 7)
	{
		cpu_set_irq_line(1, 1, HOLD_LINE);
	}
}
