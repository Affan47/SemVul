regexpr_compiled_with_locker(Locker *locker, const regex_t *compiled, const char *text, int eflags)
{
	regmatch_t match[33];
	List *ret;
	int i;
	int err;

	if (!compiled || !text)
		return set_errnull(EINVAL);

	if ((err = regexec(compiled, text, 33, match, eflags)))
		return set_errnull(err);

	if (!(ret = list_create_with_locker(locker, (list_release_t *)str_release)))
		return NULL;

	for (i = 0; i < 33 && match[i].rm_so != -1; ++i)
	{
		String *m = substr(text, (ssize_t)match[i].rm_so, (ssize_t)(match[i].rm_eo - match[i].rm_so));

		if (!m)
		{
			list_release(ret);
			return NULL;
		}

		if (!list_append(ret, m))
		{
			str_release(m);
			list_release(ret);
			return NULL;
		}
	}

	return ret;
}
