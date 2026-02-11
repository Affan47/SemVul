traceprobe_split_symbol_offset(char *symbol, unsigned long *offset)
{
	char *tmp;
	int ret;

	if (!offset)
		return -EINVAL;

	tmp = strchr(symbol, '+');
	if (tmp) {

		ret = kstrtoul(tmp + 1, 0, offset);
		if (ret)
			return ret;

		*tmp = '\0';
	} else
		*offset = 0;

	return 0;
}
