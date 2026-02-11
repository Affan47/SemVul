override_config_tree_from_string(struct cmd_context *cmd,
				     const char *config_settings)
{
	struct dm_config_tree *cft_new;

	if (!(cft_new = dm_config_from_string(config_settings))) {
		log_error("Failed to set overridden configuration entries.");
		return 1;
	}

	cmd->cft = dm_config_insert_cascaded_tree(cft_new, cmd->cft);

	return 0;
}
