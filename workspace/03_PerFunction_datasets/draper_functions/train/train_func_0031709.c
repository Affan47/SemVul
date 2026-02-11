bch_read_string_list(const char *buf, const char * const list[])
{
	size_t i;
	char *s, *d = kstrndup(buf, PAGE_SIZE - 1, GFP_KERNEL);
	if (!d)
		return -ENOMEM;

	s = strim(d);

	for (i = 0; list[i]; i++)
		if (!strcmp(list[i], s))
			break;

	kfree(d);

	if (!list[i])
		return -EINVAL;

	return i;
}
