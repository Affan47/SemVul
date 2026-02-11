UT_basename(const char* path)
{
	size_t len = strlen(path);
	const char* str = &path[len];

	while(len > 0 && path[len-1] != '/')
		str = &path[--len];

	return str;
}
