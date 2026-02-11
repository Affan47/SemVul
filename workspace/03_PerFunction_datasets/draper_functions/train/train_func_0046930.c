kstruprdup(const char *str, gfp_t gfp)
{
	char *ret, *ustr;

	ustr = ret = kmalloc(strlen(str) + 1, gfp);

	if (!ret)
		return NULL;

	while (*str)
		*ustr++ = toupper(*str++);

	*ustr = 0;

	return ret;
}
