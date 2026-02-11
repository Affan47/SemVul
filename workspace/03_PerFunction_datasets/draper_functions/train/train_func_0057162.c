powerclamp_create_debug_files(void)
{
	debug_dir = debugfs_create_dir("intel_powerclamp", NULL);
	if (!debug_dir)
		return;

	if (!debugfs_create_file("powerclamp_calib", S_IRUGO, debug_dir,
					cal_data, &powerclamp_debug_fops))
		goto file_error;

	return;

file_error:
	debugfs_remove_recursive(debug_dir);
}
