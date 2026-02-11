subsystem_release(struct inode *inode, struct file *file)
{
	struct trace_subsystem_dir *dir = file->private_data;

	trace_array_put(dir->tr);


	if (dir->subsystem)
		put_system(dir);
	else
		kfree(dir);

	return 0;
}
