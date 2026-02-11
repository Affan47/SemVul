wt_status_print_untracked(struct wt_status *s)
{
	struct dir_struct dir;
	const char *x;
	int i;
	int shown_header = 0;

	memset(&dir, 0, sizeof(dir));

	dir.exclude_per_dir = ".gitignore";
	if (!s->untracked) {
		dir.show_other_directories = 1;
		dir.hide_empty_directories = 1;
	}
	x = git_path("info/exclude");
	if (file_exists(x))
		add_excludes_from_file(&dir, x);
	if (excludes_file && file_exists(excludes_file))
		add_excludes_from_file(&dir, excludes_file);

	read_directory(&dir, ".", "", 0, NULL);
	for(i = 0; i < dir.nr; i++) {


		struct dir_entry *ent = dir.entries[i];
		int pos = cache_name_pos(ent->name, ent->len);
		struct cache_entry *ce;
		if (0 <= pos)
			die("bug in wt_status_print_untracked");
		pos = -pos - 1;
		if (pos < active_nr) {
			ce = active_cache[pos];
			if (ce_namelen(ce) == ent->len &&
			    !memcmp(ce->name, ent->name, ent->len))
				continue;
		}
		if (!shown_header) {
			s->workdir_untracked = 1;
			wt_status_print_header("Untracked files",
					       use_add_to_include_msg);
			shown_header = 1;
		}
		color_printf(color(WT_STATUS_HEADER), "#\t");
		color_printf_ln(color(WT_STATUS_UNTRACKED), "%.*s",
				ent->len, ent->name);
	}
}
