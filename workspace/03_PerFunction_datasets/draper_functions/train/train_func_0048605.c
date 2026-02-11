ima_file_mmap(struct file *file, unsigned long prot)
{
	if (file && (prot & PROT_EXEC))
		return process_measurement(file, MAY_EXEC, MMAP_CHECK, 0);
	return 0;
}
