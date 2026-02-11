activecpu_geticount(void)
{
	int result;


	VERIFY_EXECUTINGCPU(0, cpu_geticount);
	result = TIME_TO_CYCLES(activecpu, cpu[activecpu].vblankint_period - timer_timeelapsed(cpu[activecpu].vblankint_timer));
	return (result < 0) ? 0 : result;
}
