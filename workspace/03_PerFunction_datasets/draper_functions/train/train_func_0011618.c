show_files(struct dir_struct *dir, const char *prefix)
{
	int i;


	if (show_others || show_killed) {
		const char *path = ".", *base = "";
		int baselen = prefix_len;

		if (baselen)
			path = base = prefix;
		read_directory(dir, path, base, baselen, pathspec);
		if (show_others)
			show_other_files(dir);
		if (show_killed)
			show_killed_files(dir);
	}
	if (show_cached | show_stage) {
		for (i = 0; i < active_nr; i++) {
			struct cache_entry *ce = active_cache[i];
			if (excluded(dir, ce->name) != dir->show_ignored)
				continue;
			if (show_unmerged && !ce_stage(ce))
				continue;
			show_ce_entry(ce_stage(ce) ? tag_unmerged : tag_cached, ce);
		}
	}
	if (show_deleted | show_modified) {
		for (i = 0; i < active_nr; i++) {
			struct cache_entry *ce = active_cache[i];
			struct stat st;
			int err;
			if (excluded(dir, ce->name) != dir->show_ignored)
				continue;
			err = lstat(ce->name, &st);
			if (show_deleted && err)
				show_ce_entry(tag_removed, ce);
			if (show_modified && ce_modified(ce, &st, 0))
				show_ce_entry(tag_modified, ce);
		}
	}
}
