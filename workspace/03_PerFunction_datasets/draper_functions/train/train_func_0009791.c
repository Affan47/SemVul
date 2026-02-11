add_break(unsigned long ip, const char *old)
{
	unsigned char replaced[MCOUNT_INSN_SIZE];
	unsigned char brk = BREAKPOINT_INSTRUCTION;

	if (probe_kernel_read(replaced, (void *)ip, MCOUNT_INSN_SIZE))
		return -EFAULT;


	if (memcmp(replaced, old, MCOUNT_INSN_SIZE) != 0)
		return -EINVAL;

	return ftrace_write(ip, &brk, 1);
}
