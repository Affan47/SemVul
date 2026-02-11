get_sha1_with_mode_1(const char *name, unsigned char *sha1, unsigned *mode, int gently, const char *prefix)
{
	int ret, bracket_depth;
	int namelen = strlen(name);
	const char *cp;

	*mode = S_IFINVALID;
	ret = get_sha1_1(name, namelen, sha1);
	if (!ret)
		return ret;


	if (name[0] == ':') {
		int stage = 0;
		struct cache_entry *ce;
		int pos;
		if (namelen > 2 && name[1] == '/')
			return get_sha1_oneline(name + 2, sha1);
		if (namelen < 3 ||
		    name[2] != ':' ||
		    name[1] < '0' || '3' < name[1])
			cp = name + 1;
		else {
			stage = name[1] - '0';
			cp = name + 3;
		}
		namelen = namelen - (cp - name);
		if (!active_cache)
			read_cache();
		pos = cache_name_pos(cp, namelen);
		if (pos < 0)
			pos = -pos - 1;
		while (pos < active_nr) {
			ce = active_cache[pos];
			if (ce_namelen(ce) != namelen ||
			    memcmp(ce->name, cp, namelen))
				break;
			if (ce_stage(ce) == stage) {
				hashcpy(sha1, ce->sha1);
				*mode = ce->ce_mode;
				return 0;
			}
			pos++;
		}
		if (!gently)
			diagnose_invalid_index_path(stage, prefix, cp);
		return -1;
	}
	for (cp = name, bracket_depth = 0; *cp; cp++) {
		if (*cp == '{')
			bracket_depth++;
		else if (bracket_depth && *cp == '}')
			bracket_depth--;
		else if (!bracket_depth && *cp == ':')
			break;
	}
	if (*cp == ':') {
		unsigned char tree_sha1[20];
		char *object_name = NULL;
		if (!gently) {
			object_name = xmalloc(cp-name+1);
			strncpy(object_name, name, cp-name);
			object_name[cp-name] = '\0';
		}
		if (!get_sha1_1(name, cp-name, tree_sha1)) {
			const char *filename = cp+1;
			ret = get_tree_entry(tree_sha1, filename, sha1, mode);
			if (!gently) {
				diagnose_invalid_sha1_path(prefix, filename,
							   tree_sha1, object_name);
				free(object_name);
			}
			return ret;
		} else {
			if (!gently)
				die("Invalid object name '%s'.", object_name);
		}
	}
	return ret;
}
