xqmstat_proc_show(struct seq_file *m, void *v)
{
	int j;

	seq_printf(m, "qm");
	for (j = XFSSTAT_END_IBT_V2; j < XFSSTAT_END_XQMSTAT; j++)
		seq_printf(m, " %u", counter_val(xfsstats.xs_stats, j));
	seq_putc(m, '\n');
	return 0;
}
