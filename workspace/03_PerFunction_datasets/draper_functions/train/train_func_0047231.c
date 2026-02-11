config_read_branches(const char *key, const char *value, void *cb)
{
	if (!prefixcmp(key, "branch.")) {
		const char *orig_key = key;
		char *name;
		struct string_list_item *item;
		struct branch_info *info;
		enum { REMOTE, MERGE, REBASE } type;

		key += 7;
		if (!postfixcmp(key, ".remote")) {
			name = xstrndup(key, strlen(key) - 7);
			type = REMOTE;
		} else if (!postfixcmp(key, ".merge")) {
			name = xstrndup(key, strlen(key) - 6);
			type = MERGE;
		} else if (!postfixcmp(key, ".rebase")) {
			name = xstrndup(key, strlen(key) - 7);
			type = REBASE;
		} else
			return 0;

		item = string_list_insert(&branch_list, name);

		if (!item->util)
			item->util = xcalloc(sizeof(struct branch_info), 1);
		info = item->util;
		if (type == REMOTE) {
			if (info->remote_name)
				warning("more than one %s", orig_key);
			info->remote_name = xstrdup(value);
		} else if (type == MERGE) {
			char *space = strchr(value, ' ');
			value = abbrev_branch(value);
			while (space) {
				char *merge;
				merge = xstrndup(value, space - value);
				string_list_append(&info->merge, merge);
				value = abbrev_branch(space + 1);
				space = strchr(value, ' ');
			}
			string_list_append(&info->merge, xstrdup(value));
		} else
			info->rebase = git_config_bool(orig_key, value);
	}
	return 0;
}
