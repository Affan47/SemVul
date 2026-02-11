cpunum_is_suspended(int cpunum, int reason)
{
	VERIFY_CPUNUM(0, cpunum_suspend);
	return ((cpu[cpunum].nextsuspend & reason) != 0);
}
