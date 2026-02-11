xenbus_directory(struct xenbus_transaction t,
			const char *dir, const char *node, unsigned int *num)
{
	char *strings, *path;
	unsigned int len;

	path = join(dir, node);
	if (IS_ERR(path))
		return (char **)path;

	strings = xs_single(t, XS_DIRECTORY, path, &len);
	kfree(path);
	if (IS_ERR(strings))
		return (char **)strings;

	return split(strings, len, num);
}
