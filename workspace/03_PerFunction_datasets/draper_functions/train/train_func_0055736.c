lv_passes_auto_activation_filter(struct cmd_context *cmd, struct logical_volume *lv)
{
	const struct dm_config_node *cn;

	if (!(cn = find_config_tree_node(cmd, "activation/auto_activation_volume_list"))) {
		log_verbose("activation/auto_activation_volume_list configuration setting "
			    "not defined: All logical volumes will be auto-activated.");
		return 1;
	}

	return _lv_passes_volumes_filter(cmd, lv, cn, "activation/auto_activation_volume_list");
}
