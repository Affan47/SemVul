tool_init(void)
{
	int rc;

	if (debugfs_initialized())
		tool_dbgfs = debugfs_create_dir(KBUILD_MODNAME, NULL);

	rc = ntb_register_client(&tool_client);
	if (rc)
		goto err_client;

	return 0;

err_client:
	debugfs_remove_recursive(tool_dbgfs);
	return rc;
}
