speakup_file_write(struct file *fp, const char __user *buffer,
				  size_t nbytes, loff_t *ppos)
{
	size_t count = nbytes;
	const char __user *ptr = buffer;
	size_t bytes;
	unsigned long flags;
	u_char buf[256];

	if (!synth)
		return -ENODEV;
	while (count > 0) {
		bytes = min(count, sizeof(buf));
		if (copy_from_user(buf, ptr, bytes))
			return -EFAULT;
		count -= bytes;
		ptr += bytes;
		spin_lock_irqsave(&speakup_info.spinlock, flags);
		synth_write(buf, bytes);
		spin_unlock_irqrestore(&speakup_info.spinlock, flags);
	}
	return (ssize_t) nbytes;
}
