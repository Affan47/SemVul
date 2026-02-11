cpu_yielduntil_trigger(int trigger)
{
	int cpunum = cpu_getexecutingcpu();

	VERIFY_EXECUTINGCPU_VOID(cpu_yielduntil_trigger);


	cpunum_suspend(cpunum, SUSPEND_REASON_TRIGGER, 0);


	cpu[cpunum].trigger = trigger;
}
