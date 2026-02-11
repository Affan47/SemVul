cpunum_get_clockscale(int cpunum)
{
	VERIFY_CPUNUM(1.0, cpunum_get_clockscale);
	return cpu[cpunum].clockscale;
}
