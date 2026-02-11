cpunum_dasm(int cpunum, char *buffer, unsigned pc)
{
	unsigned result;
	VERIFY_CPUNUM(1, cpunum_dasm);
	cpuintrf_push_context(cpunum);
	result = internal_dasm(cpunum, buffer, pc);
	cpuintrf_pop_context();
	return result;
}
