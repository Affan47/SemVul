pstore_file_read(struct file *file, char __user *userbuf,
						size_t count, loff_t *ppos)
{
	struct seq_file *sf = file->private_data;
	struct pstore_private *ps = sf->private;

	if (ps->type == PSTORE_TYPE_FTRACE)
		return seq_read(file, userbuf, count, ppos);
	return simple_read_from_buffer(userbuf, count, ppos, ps->data, ps->size);
}
