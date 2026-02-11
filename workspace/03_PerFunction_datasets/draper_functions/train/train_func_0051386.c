get_integer(const char *buf, size_t count)
{
	char tmp[10 + 1] = { 0 };
	int ret = -EINVAL;

	if (count == 0)
		goto out;
	count = min_t(size_t, count, 10);
	memcpy(tmp, buf, count);
	ret = simple_strtol(tmp, NULL, 10);
      out:
	return ret;
}
