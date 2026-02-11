str_regsub_compiled(const regex_t *compiled, const char *replacement, String *text, int eflags, int all)
{
	String *ret;
	int err;

	if (!compiled || !replacement || !text)
		return set_errnull(EINVAL);

	if ((err = str_wrlock(text)))
		return set_errnull(err);

	ret = str_regsub_compiled_unlocked(compiled, replacement, text, eflags, all);

	if ((err = str_unlock(text)))
		return set_errnull(err);

	return ret;
}
