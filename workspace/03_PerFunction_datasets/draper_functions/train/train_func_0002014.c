select_commit_parent(const char *id, char rev[SIZEOF_REV], const char *path)
{
	char buf[SIZEOF_STR * 4];
	const char *revlist_argv[] = {
		"git", "log", "--no-color", "-1",
			"--pretty=format:%P", id, "--", path, NULL
	};
	int parents;

	if (!io_run_buf(revlist_argv, buf, sizeof(buf)) ||
	    (parents = strlen(buf) / 40) < 0) {
		report("Failed to get parent information");
		return FALSE;

	} else if (parents == 0) {
		if (path)
			report("Path '%s' does not exist in the parent", path);
		else
			report("The selected commit has no parents");
		return FALSE;
	}

	if (parents == 1)
		parents = 0;
	else if (!open_commit_parent_menu(buf, &parents))
		return FALSE;

	string_copy_rev(rev, &buf[41 * parents]);
	return TRUE;
}
