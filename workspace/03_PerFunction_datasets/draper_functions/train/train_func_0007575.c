quote_with_locker(Locker *locker, const char *str, const char *quotable, char quote_char)
{
	String *ret;
	size_t i;

	if (!str || !quotable)
		return set_errnull(EINVAL);

	if (!(ret = str_create_with_locker(locker, "%s", str)))
		return NULL;

	for (i = 0; i < ret->length - 1; ++i)
	{
		if (strchr(quotable, ret->str[i]))
		{
			if (!str_insert(ret, i++, "%c", quote_char))
			{
				str_release(ret);
				return NULL;
			}
		}
	}

	return ret;
}
