dir_len(struct mtree_entry *me)
{
	const char *path, *r;

	path = me->pathname;
	r = strrchr(path, '/');
	if (r == NULL)
		return (0);

	return (r - path + 1);
}
