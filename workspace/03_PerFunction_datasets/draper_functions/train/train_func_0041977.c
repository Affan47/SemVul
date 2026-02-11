add_reflog_for_walk(struct reflog_walk_info *info,
		struct commit *commit, const char *name)
{
	unsigned long timestamp = 0;
	int recno = -1;
	struct path_list_item *item;
	struct complete_reflogs *reflogs;
	char *branch, *at = strchr(name, '@');
	struct commit_reflog *commit_reflog;

	if (commit->object.flags & UNINTERESTING)
		die ("Cannot walk reflogs for %s", name);

	branch = xstrdup(name);
	if (at && at[1] == '{') {
		char *ep;
		branch[at - name] = '\0';
		recno = strtoul(at + 2, &ep, 10);
		if (*ep != '}') {
			recno = -1;
			timestamp = approxidate(at + 2);
		}
	} else
		recno = 0;

	item = path_list_lookup(branch, &info->complete_reflogs);
	if (item)
		reflogs = item->util;
	else {
		if (*branch == '\0') {
			unsigned char sha1[20];
			const char *head = resolve_ref("HEAD", sha1, 0, NULL);
			if (!head)
				die ("No current branch");
			free(branch);
			branch = xstrdup(head);
		}
		reflogs = read_complete_reflog(branch);
		if (!reflogs || reflogs->nr == 0) {
			unsigned char sha1[20];
			char *b;
			if (dwim_log(branch, strlen(branch), sha1, &b) == 1) {
				if (reflogs) {
					free(reflogs->ref);
					free(reflogs);
				}
				free(branch);
				branch = b;
				reflogs = read_complete_reflog(branch);
			}
		}
		if (!reflogs || reflogs->nr == 0)
			die("No reflogs found for '%s'", branch);
		path_list_insert(branch, &info->complete_reflogs)->util
			= reflogs;
	}

	commit_reflog = xcalloc(sizeof(struct commit_reflog), 1);
	if (recno < 0) {
		commit_reflog->flag = 1;
		commit_reflog->recno = get_reflog_recno_by_time(reflogs, timestamp);
		if (commit_reflog->recno < 0) {
			free(branch);
			free(commit_reflog);
			return;
		}
	} else
		commit_reflog->recno = reflogs->nr - recno - 1;
	commit_reflog->reflogs = reflogs;

	add_commit_info(commit, commit_reflog, &info->reflogs);
}
