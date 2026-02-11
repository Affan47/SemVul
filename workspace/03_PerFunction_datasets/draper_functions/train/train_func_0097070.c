get_df_full(char *dir_name)
{
	struct statfs fs_buf;
	float df_used, used_blocks;
	int df_percent_used;

	if (statfs(dir_name, &fs_buf) == -1) {
		fprintf(stderr, "fs_mark: statfs failed on %s %s\n", dir_name,
			strerror(errno));
		cleanup_exit();
	}

	used_blocks = (float)(fs_buf.f_blocks - fs_buf.f_bavail);

	df_used = (used_blocks / fs_buf.f_blocks);

	df_percent_used = (int)(100 * df_used);

	return (df_percent_used);
}
