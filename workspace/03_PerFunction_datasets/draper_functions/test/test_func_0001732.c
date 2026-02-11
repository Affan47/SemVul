trace_show(struct seq_file *m, void *v)
{
	return atomic_read(&trace_count);
}
