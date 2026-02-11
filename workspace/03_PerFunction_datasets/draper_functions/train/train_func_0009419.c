sge_queue_next(struct seq_file *seq, void *v, loff_t *pos)
{
	int entries = sge_queue_entries(seq->private);

	++*pos;
	return *pos < entries ? (void *)((uintptr_t)*pos + 1) : NULL;
}
