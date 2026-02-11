git_packfile_unpack_header(
		size_t *size_p,
		git_otype *type_p,
		git_mwindow_file *mwf,
		git_mwindow **w_curs,
		off_t *curpos)
{
	unsigned char *base;
	unsigned int left;
	unsigned long used;


	base = git_mwindow_open(mwf, w_curs, *curpos, 20, &left);
	if (base == NULL)
		return GIT_ENOMEM;

	used = packfile_unpack_header1(size_p, type_p, base, left);

	if (used == 0)
		return git__throw(GIT_EOBJCORRUPTED, "Header length is zero");

	*curpos += used;
	return GIT_SUCCESS;
}
