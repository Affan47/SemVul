download_func(const char *p, size_t cnt, void *voidptr)
{
	if (fwrite(p, 1, cnt, stdout) != cnt)
		return (-1);
	return (0);
}
