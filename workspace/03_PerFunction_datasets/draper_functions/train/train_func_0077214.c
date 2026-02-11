find_mount_table(struct mount_table *mtab, const char *text)
{
	ssize_t count;
	char *file_mem;
	size_t file_size;

	file_mem = file_read_mounts(&file_size);
	if (file_mem == NULL)
	{
		pr_red_info("file_read_mounts");
		return -EFAULT;
	}

	count = find_mount_table_base(file_mem, mtab, text) ? 0 : -ENODATA;
	free(file_mem);

	return count;
}
