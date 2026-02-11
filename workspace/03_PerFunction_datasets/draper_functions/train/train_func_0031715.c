str_uc_unlocked(String *str)
{
	size_t i;

	if (!str)
		return set_errnull(EINVAL);

	for (i = 0; i < str->length - 1; ++i)
		str->str[i] = to_upper(str->str[i]);

	return str;
}
