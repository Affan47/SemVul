process_directory(const char *path, int len, struct stat *st)
{
	unsigned char sha1[20];
	int pos = cache_name_pos(path, len);


	if (pos >= 0) {
		struct cache_entry *ce = active_cache[pos];
		if (S_ISGITLINK(ce->ce_mode)) {


			if (resolve_gitlink_ref(path, "HEAD", sha1) < 0)
				return 0;

			return add_one_path(ce, path, len, st);
		}

		return remove_one_path(path);
	}


	pos = -pos-1;
	while (pos < active_nr) {
		struct cache_entry *ce = active_cache[pos++];

		if (strncmp(ce->name, path, len))
			break;
		if (ce->name[len] > '/')
			break;
		if (ce->name[len] < '/')
			continue;


		return error("%s: is a directory - add individual files instead", path);
	}


	if (!resolve_gitlink_ref(path, "HEAD", sha1))
		return add_one_path(NULL, path, len, st);


	return error("%s: is a directory - add files inside instead", path);
}
