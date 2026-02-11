blob_content_to_link(
	struct stat *st,
	git_blob *blob,
	const char *path,
	mode_t dir_mode,
	int can_symlink)
{
	git_buf linktarget = GIT_BUF_INIT;
	int error;

	if ((error = git_futils_mkpath2file(path, dir_mode)) < 0)
		return error;

	if ((error = git_blob__getbuf(&linktarget, blob)) < 0)
		return error;

	if (can_symlink) {
		if ((error = p_symlink(git_buf_cstr(&linktarget), path)) < 0)
			giterr_set(GITERR_OS, "Could not create symlink %s\n", path);
	} else {
		error = git_futils_fake_symlink(git_buf_cstr(&linktarget), path);
	}

	if (!error) {
		if ((error = p_lstat(path, st)) < 0)
			giterr_set(GITERR_CHECKOUT, "Could not stat symlink %s", path);

		st->st_mode = GIT_FILEMODE_LINK;
	}

	git_buf_free(&linktarget);

	return error;
}
