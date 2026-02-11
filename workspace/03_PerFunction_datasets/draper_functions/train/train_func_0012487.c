delete_sibling_file(const char *base, const char *extension)
{
	struct stat st;
	char *path;

	x_asprintf(&path, "%s%s", base, extension);
	if (lstat(path, &st) == 0) {
		delete_file(path, file_size(&st) / 1024);
	} else if (errno != ENOENT) {
		fprintf(stderr, "ccache: failed to stat %s (%s)\n",
			path, strerror(errno));
	}
	free(path);
}
