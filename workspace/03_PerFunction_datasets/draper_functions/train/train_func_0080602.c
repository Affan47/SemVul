proc_exe_link(struct dentry *dentry, struct path *exe_path)
{
	struct task_struct *task;
	struct file *exe_file;

	task = get_proc_task(d_inode(dentry));
	if (!task)
		return -ENOENT;
	exe_file = get_task_exe_file(task);
	put_task_struct(task);
	if (exe_file) {
		*exe_path = exe_file->f_path;
		path_get(&exe_file->f_path);
		fput(exe_file);
		return 0;
	} else
		return -ENOENT;
}
