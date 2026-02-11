dump_stdout(const char *p, size_t l, void *dummy)
{
	if (l == 0)
		return 0;

	if (fwrite(p, l, 1, stdout) != 1)
		exit(1);
	fflush(stdout);
	return (0);
}
