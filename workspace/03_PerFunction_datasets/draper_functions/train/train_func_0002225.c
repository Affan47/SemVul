do_plain_rerere(struct string_list *rr, int fd)
{
	struct string_list conflict = STRING_LIST_INIT_DUP;
	struct string_list update = STRING_LIST_INIT_DUP;
	int i;

	find_conflict(&conflict);


	for (i = 0; i < conflict.nr; i++) {
		const char *path = conflict.items[i].string;
		if (!string_list_has_string(rr, path)) {
			unsigned char sha1[20];
			char *hex;
			int ret;
			ret = handle_file(path, sha1, NULL);
			if (ret < 1)
				continue;
			hex = xstrdup(sha1_to_hex(sha1));
			string_list_insert(rr, path)->util = hex;
			if (mkdir(git_path("rr-cache/%s", hex), 0755))
				continue;
			handle_file(path, NULL, rerere_path(hex, "preimage"));
			fprintf(stderr, "Recorded preimage for '%s'\n", path);
		}
	}


	for (i = 0; i < rr->nr; i++) {
		int ret;
		const char *path = rr->items[i].string;
		const char *name = (const char *)rr->items[i].util;

		if (has_rerere_resolution(name)) {
			if (!merge(name, path)) {
				if (rerere_autoupdate)
					string_list_insert(&update, path);
				fprintf(stderr,
					"%s '%s' using previous resolution.\n",
					rerere_autoupdate
					? "Staged" : "Resolved",
					path);
				goto mark_resolved;
			}
		}


		ret = handle_file(path, NULL, NULL);
		if (ret)
			continue;

		fprintf(stderr, "Recorded resolution for '%s'.\n", path);
		copy_file(rerere_path(name, "postimage"), path, 0666);
	mark_resolved:
		rr->items[i].util = NULL;
	}

	if (update.nr)
		update_paths(&update);

	return write_rr(rr, fd);
}
