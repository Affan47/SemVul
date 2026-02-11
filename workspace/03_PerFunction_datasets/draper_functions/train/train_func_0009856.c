tree_entry_interesting(const struct name_entry *entry,
			   struct strbuf *base, int base_offset,
			   const struct pathspec *ps)
{
	int i;
	int pathlen, baselen = base->len - base_offset;
	int never_interesting = ps->has_wildcard ? 0 : -1;

	if (!ps->nr) {
		if (!ps->recursive || ps->max_depth == -1)
			return 2;
		return !!within_depth(base->buf + base_offset, baselen,
				      !!S_ISDIR(entry->mode),
				      ps->max_depth);
	}

	pathlen = tree_entry_len(entry->path, entry->sha1);

	for (i = ps->nr - 1; i >= 0; i--) {
		const struct pathspec_item *item = ps->items+i;
		const char *match = item->match;
		const char *base_str = base->buf + base_offset;
		int matchlen = item->len;

		if (baselen >= matchlen) {

			if (!match_dir_prefix(base_str, baselen, match, matchlen))
				goto match_wildcards;

			if (!ps->recursive || ps->max_depth == -1)
				return 2;

			return !!within_depth(base_str + matchlen + 1,
					      baselen - matchlen - 1,
					      !!S_ISDIR(entry->mode),
					      ps->max_depth);
		}


		if (!strncmp(base_str, match, baselen)) {
			if (match_entry(entry, pathlen,
					match + baselen, matchlen - baselen,
					&never_interesting))
				return 1;

			if (ps->items[i].use_wildcard) {
				if (!fnmatch(match + baselen, entry->path, 0))
					return 1;


				if (ps->recursive && S_ISDIR(entry->mode))
					return 1;
			}

			continue;
		}

match_wildcards:
		if (!ps->items[i].use_wildcard)
			continue;


		strbuf_add(base, entry->path, pathlen);

		if (!fnmatch(match, base->buf + base_offset, 0)) {
			strbuf_setlen(base, base_offset + baselen);
			return 1;
		}
		strbuf_setlen(base, base_offset + baselen);


		if (ps->recursive && S_ISDIR(entry->mode))
			return 1;
	}
	return never_interesting;
}
