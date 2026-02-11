shell_exec_memory_stats_halloc(struct gnutella_shell *sh,
	unsigned opt, unsigned which)
{
	if (which & STATS_USAGE)
		return memory_stats_unsupported(sh, "halloc", STATS_USAGE_STR);

	return memory_run_opt_shower(sh, halloc_dump_stats_log, "HALLOC ", opt);
}
