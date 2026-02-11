_set_tag(struct cmd_context *cmd, const char *tag)
{
	log_very_verbose("Setting host tag: %s", dm_pool_strdup(cmd->libmem, tag));

	if (!str_list_add(cmd->libmem, &cmd->tags, tag)) {
		log_error("_set_tag: str_list_add %s failed", tag);
		return 0;
	}

	return 1;
}
