set_DAC_volt(double volt)
{
    DAC_voltage = volt;
    if ((value.get() & (CPSON|CPSRM)) == (CPSON|CPSRM))
	calculate_freq();
}
