cpufreq_p4_get(unsigned int cpu)
{
	u32 l, h;

	rdmsr_on_cpu(cpu, MSR_IA32_THERM_CONTROL, &l, &h);

	if (l & 0x10) {
		l = l >> 1;
		l &= 0x7;
	} else
		l = DC_DISABLE;

	if (l != DC_DISABLE)
		return stock_freq * l / 8;

	return stock_freq;
}
