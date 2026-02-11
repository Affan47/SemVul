xenbus_read(struct xenbus_transaction t,
		  const char *dir, const char *node, unsigned int *len)
{
	char *path;
	void *ret;

	path = join(dir, node);
	if (IS_ERR(path))
		return (void *)path;

	ret = xs_single(t, XS_READ, path, len);
	kfree(path);
	return ret;
}
