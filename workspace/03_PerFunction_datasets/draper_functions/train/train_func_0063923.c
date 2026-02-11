kdb_ef(int argc, const char **argv)
{
	int diag;
	unsigned long addr;
	long offset;
	int nextarg;

	if (argc != 1)
		return KDB_ARGCOUNT;

	nextarg = 1;
	diag = kdbgetaddrarg(argc, argv, &nextarg, &addr, &offset, NULL);
	if (diag)
		return diag;
	show_regs((struct pt_regs *)addr);
	return 0;
}
