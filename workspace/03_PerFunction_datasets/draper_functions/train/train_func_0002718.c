git__fnmatch(const char *pattern, const char *name, int flags)
{
	int ret;

	ret = p_fnmatch(pattern, name, flags);
	switch (ret) {
	case 0:
		return GIT_SUCCESS;
	case FNM_NOMATCH:
		return GIT_ENOMATCH;
	default:
		return git__throw(GIT_EOSERR, "Error trying to match path");
	}
}
