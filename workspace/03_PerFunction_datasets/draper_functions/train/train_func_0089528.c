ptc_seq_start(struct seq_file *file, loff_t *offset)
{
	if (*offset < num_possible_cpus())
		return offset;
	return NULL;
}
