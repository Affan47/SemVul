diff_change(struct diff_options *options,
		 unsigned old_mode, unsigned new_mode,
		 const unsigned char *old_sha1,
		 const unsigned char *new_sha1,
		 const char *base, const char *path)
{
	char concatpath[PATH_MAX];
	struct diff_filespec *one, *two;

	if (options->reverse_diff) {
		unsigned tmp;
		const unsigned char *tmp_c;
		tmp = old_mode; old_mode = new_mode; new_mode = tmp;
		tmp_c = old_sha1; old_sha1 = new_sha1; new_sha1 = tmp_c;
	}
	if (!path) path = "";
	sprintf(concatpath, "%s%s", base, path);
	one = alloc_filespec(concatpath);
	two = alloc_filespec(concatpath);
	fill_filespec(one, old_sha1, old_mode);
	fill_filespec(two, new_sha1, new_mode);

	diff_queue(&diff_queued_diff, one, two);
	options->has_changes = 1;
}
