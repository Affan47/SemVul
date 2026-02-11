parse_memtest(char *arg)
{
	int ret = 0;

	if (arg)
		ret = kstrtouint(arg, 0, &memtest_pattern);
	else
		memtest_pattern = ARRAY_SIZE(patterns);

	return ret;
}
