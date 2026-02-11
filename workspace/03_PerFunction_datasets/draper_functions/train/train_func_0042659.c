apply_patch(int fd, const char *filename, int inaccurate_eof)
{
	size_t offset;
	struct strbuf buf;
	struct patch *list = NULL, **listp = &list;
	int skipped_patch = 0;

	strbuf_init(&buf, 0);
	patch_input_file = filename;
	read_patch_file(&buf, fd);
	offset = 0;
	while (offset < buf.len) {
		struct patch *patch;
		int nr;

		patch = xcalloc(1, sizeof(*patch));
		patch->inaccurate_eof = inaccurate_eof;
		nr = parse_chunk(buf.buf + offset, buf.len - offset, patch);
		if (nr < 0)
			break;
		if (apply_in_reverse)
			reverse_patches(patch);
		if (prefix)
			prefix_patches(patch);
		if (use_patch(patch)) {
			patch_stats(patch);
			*listp = patch;
			listp = &patch->next;
		}
		else {

			free(patch);
			skipped_patch++;
		}
		offset += nr;
	}

	if (whitespace_error && (ws_error_action == die_on_ws_error))
		apply = 0;

	update_index = check_index && apply;
	if (update_index && newfd < 0)
		newfd = hold_locked_index(&lock_file, 1);

	if (check_index) {
		if (read_cache() < 0)
			die("unable to read index file");
	}

	if ((check || apply) &&
	    check_patch_list(list) < 0 &&
	    !apply_with_reject)
		exit(1);

	if (apply && write_out_results(list, skipped_patch))
		exit(1);

	if (fake_ancestor)
		build_fake_ancestor(list, fake_ancestor);

	if (diffstat)
		stat_patch_list(list);

	if (numstat)
		numstat_patch_list(list);

	if (summary)
		summary_patch_list(list);

	strbuf_release(&buf);
	return 0;
}
