builtin_diff_b_f(struct rev_info *revs,
			    int argc, const char **argv,
			    struct blobinfo *blob,
			    const char *path)
{

	struct stat st;

	if (argc > 1)
		usage(builtin_diff_usage);

	if (lstat(path, &st))
		die_errno("failed to stat '%s'", path);
	if (!(S_ISREG(st.st_mode) || S_ISLNK(st.st_mode)))
		die("'%s': not a regular file or symlink", path);

	diff_set_mnemonic_prefix(&revs->diffopt, "o/", "w/");

	if (blob[0].mode == S_IFINVALID)
		blob[0].mode = canon_mode(st.st_mode);

	stuff_change(&revs->diffopt,
		     blob[0].mode, canon_mode(st.st_mode),
		     blob[0].sha1, null_sha1,
		     path, path);
	diffcore_std(&revs->diffopt);
	diff_flush(&revs->diffopt);
	return 0;
}
