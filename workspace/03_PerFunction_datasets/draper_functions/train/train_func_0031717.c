wil6210_debugfs_init_files(struct wil6210_priv *wil,
				       struct dentry *dbg)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(dbg_files); i++)
		debugfs_create_file(dbg_files[i].name, dbg_files[i].mode, dbg,
				    wil, dbg_files[i].fops);
}
