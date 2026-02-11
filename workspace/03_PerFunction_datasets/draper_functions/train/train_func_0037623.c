verify_absent(const char *path, const char *action,
		struct unpack_trees_options *o)
{
	struct stat st;

	if (o->index_only || o->reset || !o->update)
		return;

	if (!lstat(path, &st)) {
		int cnt;

		if (o->dir && excluded(o->dir, path))


			return;
		if (S_ISDIR(st.st_mode)) {


			cnt = verify_clean_subdirectory(path, action, o);


			o->pos += cnt;
			return;
		}


		cnt = cache_name_pos(path, strlen(path));
		if (0 <= cnt) {
			struct cache_entry *ce = active_cache[cnt];
			if (!ce_stage(ce) && !ce->ce_mode)
				return;
		}

		die("Untracked working tree file '%s' "
		    "would be %s by merge.", path, action);
	}
}
