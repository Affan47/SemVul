repack_without_ref(const char *refname)
{
	struct ref_list *list, *packed_ref_list;
	int fd;
	int found = 0;

	packed_ref_list = get_packed_refs();
	for (list = packed_ref_list; list; list = list->next) {
		if (!strcmp(refname, list->name)) {
			found = 1;
			break;
		}
	}
	if (!found)
		return 0;
	fd = hold_lock_file_for_update(&packlock, git_path("packed-refs"), 0);
	if (fd < 0)
		return error("cannot delete '%s' from packed refs", refname);

	for (list = packed_ref_list; list; list = list->next) {
		char line[PATH_MAX + 100];
		int len;

		if (!strcmp(refname, list->name))
			continue;
		len = snprintf(line, sizeof(line), "%s %s\n",
			       sha1_to_hex(list->sha1), list->name);

		if (len > sizeof(line))
			die("too long a refname '%s'", list->name);
		write_or_die(fd, line, len);
	}
	return commit_lock_file(&packlock);
}
