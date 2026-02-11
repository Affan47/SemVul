read_repo_config_option(char *name, size_t namelen, char *value, size_t valuelen)
{
	if (!strcmp(name, "i18n.commitencoding"))
		string_ncopy(opt_encoding, value, valuelen);

	if (!strcmp(name, "core.editor"))
		string_ncopy(opt_editor, value, valuelen);


	if (*opt_head &&
	    !strncmp(name, "branch.", 7) &&
	    !strncmp(name + 7, opt_head, strlen(opt_head)) &&
	    !strcmp(name + 7 + strlen(opt_head), ".remote"))
		string_ncopy(opt_remote, value, valuelen);

	if (*opt_head && *opt_remote &&
	    !strncmp(name, "branch.", 7) &&
	    !strncmp(name + 7, opt_head, strlen(opt_head)) &&
	    !strcmp(name + 7 + strlen(opt_head), ".merge")) {
		size_t from = strlen(opt_remote);

		if (!strncmp(value, "refs/heads/", STRING_SIZE("refs/heads/"))) {
			value += STRING_SIZE("refs/heads/");
			valuelen -= STRING_SIZE("refs/heads/");
		}

		if (!string_format_from(opt_remote, &from, "/%s", value))
			opt_remote[0] = 0;
	}

	return OK;
}
