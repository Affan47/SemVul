prune_packed_objects(int opts)
{
	int i;
	static char pathname[PATH_MAX];
	const char *dir = get_object_directory();
	int len = strlen(dir);

	if (len > PATH_MAX - 42)
		die("impossible object directory");
	memcpy(pathname, dir, len);
	if (len && pathname[len-1] != '/')
		pathname[len++] = '/';
	for (i = 0; i < 256; i++) {
		DIR *d;

		sprintf(pathname + len, "%02x/", i);
		d = opendir(pathname);
		if (opts == VERBOSE && (d || i == 255))
			fprintf(stderr, "Removing unused objects %d%%...\015",
				((i+1) * 100) / 256);
		if (!d)
			continue;
		prune_dir(i, d, pathname, len + 3, opts);
		closedir(d);
	}
	if (opts == VERBOSE)
		fprintf(stderr, "\nDone.\n");
}
