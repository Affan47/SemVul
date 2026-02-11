get_one_status(const char *path, unsigned int status, void *data)
{
	struct status_file_info *sfi = data;

	sfi->count++;
	sfi->status = status;

	if (sfi->count > 1 ||
		(strcmp(sfi->expected, path) != 0 &&
		p_fnmatch(sfi->expected, path, 0) != 0)) {
		giterr_set(GITERR_INVALID,
			"Ambiguous path '%s' given to git_status_file", sfi->expected);
		sfi->ambiguous = true;
		return GIT_EAMBIGUOUS;
	}

	return 0;
}
