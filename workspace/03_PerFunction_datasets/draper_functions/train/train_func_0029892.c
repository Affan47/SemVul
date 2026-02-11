check_local_mod(unsigned char *head, int index_only)
{


	int i, no_head;
	int errs = 0;

	no_head = is_null_sha1(head);
	for (i = 0; i < list.nr; i++) {
		struct stat st;
		int pos;
		struct cache_entry *ce;
		const char *name = list.name[i];
		unsigned char sha1[20];
		unsigned mode;
		int local_changes = 0;
		int staged_changes = 0;

		pos = cache_name_pos(name, strlen(name));
		if (pos < 0)
			continue;
		ce = active_cache[pos];

		if (lstat(ce->name, &st) < 0) {
			if (errno != ENOENT)
				warning("'%s': %s", ce->name, strerror(errno));

			continue;
		}
		else if (S_ISDIR(st.st_mode)) {


			continue;
		}


		if (ce_match_stat(ce, &st, 0))
			local_changes = 1;


		if (no_head
		     || get_tree_entry(head, name, sha1, &mode)
		     || ce->ce_mode != create_ce_mode(mode)
		     || hashcmp(ce->sha1, sha1))
			staged_changes = 1;


		if (local_changes && staged_changes) {
			if (!index_only || !(ce->ce_flags & CE_INTENT_TO_ADD))
				errs = error("'%s' has staged content different "
					     "from both the file and the HEAD\n"
					     "(use -f to force removal)", name);
		}
		else if (!index_only) {
			if (staged_changes)
				errs = error("'%s' has changes staged in the index\n"
					     "(use --cached to keep the file, "
					     "or -f to force removal)", name);
			if (local_changes)
				errs = error("'%s' has local modifications\n"
					     "(use --cached to keep the file, "
					     "or -f to force removal)", name);
		}
	}
	return errs;
}
