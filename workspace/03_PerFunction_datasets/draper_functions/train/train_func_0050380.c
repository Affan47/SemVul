lookup_addr(char *arg)
{
	unsigned long addr = 0;

	if (!strcmp(arg, "kgdbts_break_test"))
		addr = (unsigned long)kgdbts_break_test;
	else if (!strcmp(arg, "sys_open"))
		addr = (unsigned long)do_sys_open;
	else if (!strcmp(arg, "do_fork"))
		addr = (unsigned long)_do_fork;
	else if (!strcmp(arg, "hw_break_val"))
		addr = (unsigned long)&hw_break_val;
	addr = (unsigned long) dereference_function_descriptor((void *)addr);
	return addr;
}
