read_profile(struct file *file, char __user *buf, size_t count, loff_t *ppos)
{
	unsigned long p = *ppos;
	ssize_t read;
	char *pnt;
	unsigned int sample_step = 1 << prof_shift;

	profile_flip_buffers();
	if (p >= (prof_len+1)*sizeof(unsigned int))
		return 0;
	if (count > (prof_len+1)*sizeof(unsigned int) - p)
		count = (prof_len+1)*sizeof(unsigned int) - p;
	read = 0;

	while (p < sizeof(unsigned int) && count > 0) {
		if (put_user(*((char *)(&sample_step)+p), buf))
			return -EFAULT;
		buf++; p++; count--; read++;
	}
	pnt = (char *)prof_buffer + p - sizeof(atomic_t);
	if (copy_to_user(buf, (void *)pnt, count))
		return -EFAULT;
	read += count;
	*ppos += read;
	return read;
}
