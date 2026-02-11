cpunum_set_op_base(int cpunum, unsigned val)
{
	VERIFY_CPUNUM_VOID(cpunum_set_op_base);
	cpuintrf_push_context(cpunum);
	(*cpu[cpunum].intf.set_op_base)(val);
	cpuintrf_pop_context();
}
