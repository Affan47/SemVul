operator()(string const& path)
{
	if (inPaths(path, mExclude) || !inPaths(path, mInclude))
		return true;


	struct stat s;
	if (lstat(path.c_str(), &s) < 0)
		return !mLogMissing;


	return S_ISDIR(s.st_mode);
}
