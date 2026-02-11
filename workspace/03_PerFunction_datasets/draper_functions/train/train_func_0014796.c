kgdb_io_ready(int print_wait)
{
	if (!dbg_io_ops)
		return 0;
	if (kgdb_connected)
		return 1;
	if (atomic_read(&kgdb_setting_breakpoint))
		return 1;
	if (print_wait) {
#ifdef CONFIG_KGDB_KDB
		if (!dbg_kdb_mode)
			pr_crit("waiting... or $3#33 for KDB\n");
#else
		pr_crit("Waiting for remote debugger\n");
#endif
	}
	return 1;
}
