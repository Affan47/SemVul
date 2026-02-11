verify_clean_subdirectory(struct cache_entry *ce,
				      enum unpack_trees_error_types error_type,
				      struct unpack_trees_options *o)
{


	int namelen;
	int i;
	struct dir_struct d;
	char *pathbuf;
	int cnt = 0;
	unsigned char sha1[20];

	if (S_ISGITLINK(ce->ce_mode) &&
	    resolve_gitlink_ref(ce->name, "HEAD", sha1) == 0) {


		if (!hashcmp(sha1, ce->sha1))
			return 0;
		return verify_clean_submodule(ce, error_type, o);
	}


	namelen = strlen(ce->name);
	for (i = locate_in_src_index(ce, o);
	     i < o->src_index->cache_nr;
	     i++) {
		struct cache_entry *ce2 = o->src_index->cache[i];
		int len = ce_namelen(ce2);
		if (len < namelen ||
		    strncmp(ce->name, ce2->name, namelen) ||
		    ce2->name[namelen] != '/')
			break;


		if (!ce_stage(ce2)) {
			if (verify_uptodate(ce2, o))
				return -1;
			add_entry(o, ce2, CE_REMOVE, 0);
			mark_ce_used(ce2, o);
		}
		cnt++;
	}


	pathbuf = xmalloc(namelen + 2);
	memcpy(pathbuf, ce->name, namelen);
	strcpy(pathbuf+namelen, "/");

	memset(&d, 0, sizeof(d));
	if (o->dir)
		d.exclude_per_dir = o->dir->exclude_per_dir;
	i = read_directory(&d, pathbuf, namelen+1, NULL);
	if (i)
		return o->gently ? -1 :
			add_rejected_path(o, ERROR_NOT_UPTODATE_DIR, ce->name);
	free(pathbuf);
	return cnt;
}
