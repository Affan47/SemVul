ashmem_llseek(struct file *file, loff_t offset, int origin)
{
	struct ashmem_area *asma = file->private_data;
	int ret;

	mutex_lock(&ashmem_mutex);

	if (asma->size == 0) {
		ret = -EINVAL;
		goto out;
	}

	if (!asma->file) {
		ret = -EBADF;
		goto out;
	}

	ret = vfs_llseek(asma->file, offset, origin);
	if (ret < 0)
		goto out;


	file->f_pos = asma->file->f_pos;

out:
	mutex_unlock(&ashmem_mutex);
	return ret;
}
