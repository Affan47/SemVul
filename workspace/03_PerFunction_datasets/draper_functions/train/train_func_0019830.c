halt_callback(int param)
{
	int cpunum = param & 0xff;
	int state = param >> 8;


	if (state == ASSERT_LINE)
		cpunum_suspend(cpunum, SUSPEND_REASON_HALT, 1);


	else if (state == CLEAR_LINE)
		cpunum_resume(cpunum, SUSPEND_REASON_HALT);
}
