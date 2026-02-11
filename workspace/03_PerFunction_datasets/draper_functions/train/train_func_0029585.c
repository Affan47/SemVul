config_files_changed(struct cmd_context *cmd)
{
	struct config_tree_list *cfl;

	dm_list_iterate_items(cfl, &cmd->config_files) {
		if (config_file_changed(cfl->cft))
			return 1;
	}

	return 0;
}
