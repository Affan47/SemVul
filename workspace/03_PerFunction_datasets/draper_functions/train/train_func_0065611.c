intel_pstate_debug_expose_params(void)
{
	struct dentry *debugfs_parent;
	int i = 0;

	if (hwp_active)
		return;
	debugfs_parent = debugfs_create_dir("pstate_snb", NULL);
	if (IS_ERR_OR_NULL(debugfs_parent))
		return;
	while (pid_files[i].name) {
		debugfs_create_file(pid_files[i].name, 0660,
				    debugfs_parent, pid_files[i].value,
				    &fops_pid_param);
		i++;
	}
}
