enumerate_dir_enum(dir_enum_t *this, char **relative,
							   char **absolute, struct stat *st)
{
	struct dirent *entry = readdir(this->dir);
	size_t remaining;
	int len;

	if (!entry)
	{
		return FALSE;
	}
	if (streq(entry->d_name, ".") || streq(entry->d_name, ".."))
	{
		return enumerate_dir_enum(this, relative, absolute, st);
	}
	if (relative)
	{
		*relative = entry->d_name;
	}
	if (absolute || st)
	{
		remaining = sizeof(this->full) - (this->full_end - this->full);
		len = snprintf(this->full_end, remaining, "%s", entry->d_name);
		if (len < 0 || len >= remaining)
		{
			DBG1(DBG_LIB, "buffer too small to enumerate file '%s'",
				 entry->d_name);
			return FALSE;
		}
		if (absolute)
		{
			*absolute = this->full;
		}
		if (st)
		{
			if (stat(this->full, st))
			{
				DBG1(DBG_LIB, "stat() on '%s' failed: %s", this->full,
					 strerror(errno));
				return FALSE;
			}
		}
	}
	return TRUE;
}
