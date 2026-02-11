get_path_prefix(const char *path, size_t pathlen, size_t maxlen)
{
	size_t i = pathlen;
	if (i > maxlen)
		i = maxlen;
	do {
		i--;
	} while (i > 0 && path[i] != '/');
	return i;
}
