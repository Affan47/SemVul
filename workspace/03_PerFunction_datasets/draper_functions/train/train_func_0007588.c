str_quote_with_locker(Locker *locker, const String *str, const char *quotable, char quote_char)
{
	String *ret;
	size_t i;

	if (!str || !quotable)
		return set_errnull(EINVAL);

	if (!(ret = str_copy_with_locker(locker, str)))
		return NULL;

	for (i = 0; i < ret->length - 1; ++i)
	{
		if (ret->str[i] && strchr(quotable, ret->str[i]))
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
