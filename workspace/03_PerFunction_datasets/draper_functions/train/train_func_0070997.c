file_cache_init(const char *root)
{
	char path[PATH_MAX];
	struct stat64 buf;
	int result, i;

	struct file_cache *f = malloc(sizeof(*f));
	if(!f)
		return 0;

	f->root = strdup(root);
	if(!f->root) {
		free(f);
		return 0;
	}

	sprintf(path, "%s/ff", root);
	result = stat64(path, &buf);
	if(result != 0) {
		debug(D_CACHE, "%s does not exist, creating cache directories...", path);
		if(!create_dir(path, 0777))
			goto failure;
		sprintf(path, "%s/txn", root);
		if(!create_dir(path, 0777))
			goto failure;
		for(i = 0; i <= 0xff; i++) {
			sprintf(path, "%s/%02x", root, i);
			if(!create_dir(path, 0777) != 0)
				goto failure;
		}
	}

	return f;

      failure:
	file_cache_fini(f);
	return 0;
}
