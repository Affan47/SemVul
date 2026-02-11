wt_status_print_untracked(struct wt_status *s)
{
	struct dir_struct dir;
	int i;
	int shown_header = 0;
	struct strbuf buf;

	strbuf_init(&buf, 0);
	memset(&dir, 0, sizeof(dir));

	if (!s->untracked) {
		dir.show_other_directories = 1;
		dir.hide_empty_directories = 1;
	}
	setup_standard_excludes(&dir);

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
			wt_status_print_header(s, "Untracked files",
					       use_add_to_include_msg);
			shown_header = 1;
		}
		color_fprintf(s->fp, color(WT_STATUS_HEADER), "#\t");
		color_fprintf_ln(s->fp, color(WT_STATUS_UNTRACKED), "%s",
				quote_path(ent->name, ent->len,
					&buf, s->prefix));
	}
	strbuf_release(&buf);
}
