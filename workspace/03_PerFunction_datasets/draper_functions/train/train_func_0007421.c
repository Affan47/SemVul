proc_scsi_host_write(struct file *file, const char __user *buf,
                           size_t count, loff_t *ppos)
{
	struct Scsi_Host *shost = PDE_DATA(file_inode(file));
	ssize_t ret = -ENOMEM;
	char *page;

	if (count > PROC_BLOCK_SIZE)
		return -EOVERFLOW;

	if (!shost->hostt->write_info)
		return -EINVAL;

	page = (char *)__get_free_page(GFP_KERNEL);
	if (page) {
		ret = -EFAULT;
		if (copy_from_user(page, buf, count))
			goto out;
		ret = shost->hostt->write_info(shost, page, count);
	}
out:
	free_page((unsigned long)page);
	return ret;
}
