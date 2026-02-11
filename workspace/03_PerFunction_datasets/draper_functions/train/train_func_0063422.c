read_repo_config_option(char *name, size_t namelen, char *value, size_t valuelen, void *data)
{
	if (!strcmp(name, "gui.encoding"))
		parse_encoding(&opt_encoding, value, TRUE);

	else if (!strcmp(name, "core.editor"))
		string_ncopy(opt_editor, value, valuelen);

	else if (!strcmp(name, "core.worktree"))
		set_work_tree(value);

	else if (!prefixcmp(name, "tig.color."))
		set_repo_config_option(name + 10, value, option_color_command);

	else if (!prefixcmp(name, "tig.bind."))
		set_repo_config_option(name + 9, value, option_bind_command);

	else if (!prefixcmp(name, "tig."))
		set_repo_config_option(name + 4, value, option_set_command);

	else if (*opt_head && !prefixcmp(name, "branch.") &&
		 !strncmp(name + 7, opt_head, strlen(opt_head)))
		set_remote_branch(name + 7 + strlen(opt_head), value, valuelen);

	return OK;
}
