path_join(const char *path, size_t prefixlen,
							char buf[PATH_MAX])
{
	size_t pathlen;

	if (path[0] == '/')
		return path;

	pathlen = strlen(path);
	if (prefixlen + pathlen + 1 >= PATH_MAX)
		return NULL;

	memcpy(buf + prefixlen, path, pathlen + 1);
	return buf;
}
