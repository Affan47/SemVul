xgene_edac_l3_create_debugfs_nodes(struct edac_device_ctl_info *edac_dev)
{
	struct xgene_edac_dev_ctx *ctx = edac_dev->pvt_info;
	struct dentry *dbgfs_dir;
	char name[10];

	if (!IS_ENABLED(CONFIG_EDAC_DEBUG) || !ctx->edac->dfs)
		return;

	snprintf(name, sizeof(name), "l3c%d", ctx->edac_idx);
	dbgfs_dir = edac_debugfs_create_dir_at(name, ctx->edac->dfs);
	if (!dbgfs_dir)
		return;

	debugfs_create_file("l3_inject_ctrl", S_IWUSR, dbgfs_dir, edac_dev,
			    &xgene_edac_l3_debug_inject_fops);
}
