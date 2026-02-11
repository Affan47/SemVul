Create(const CPath& path, bool overwrite, int accessMode)
{
	if (!overwrite && path.FileExists()) {
		return false;
	}

	return Open(path, write, accessMode);
}
