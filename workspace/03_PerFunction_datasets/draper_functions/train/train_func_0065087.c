prism2_pda_proc_read(struct file *file, char __user *buf,
				    size_t count, loff_t *_pos)
{
	local_info_t *local = PDE_DATA(file_inode(file));
	size_t off;

	if (local->pda == NULL || *_pos >= PRISM2_PDA_SIZE)
		return 0;

	off = *_pos;
	if (count > PRISM2_PDA_SIZE - off)
		count = PRISM2_PDA_SIZE - off;
	if (copy_to_user(buf, local->pda + off, count) != 0)
		return -EFAULT;
	*_pos += count;
	return count;
}
