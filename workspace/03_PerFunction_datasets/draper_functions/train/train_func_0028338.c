cpunum_suspend(int cpunum, int reason, int eatcycles)
{
	VERIFY_CPUNUM_VOID(cpunum_suspend);
	LOG(("cpunum_suspend (CPU=%d, r=%X, eat=%d)\n", cpunum, reason, eatcycles));


	cpu[cpunum].nextsuspend |= reason;
	cpu[cpunum].nexteatcycles = eatcycles;
	if (cpu_getexecutingcpu() >= 0)
		activecpu_abort_timeslice();
}
