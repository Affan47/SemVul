str_trim_left_unlocked(String *str)
{
	char *s;

	if (!str)
		return set_errnull(EINVAL);

	for (s = str->str; is_space(*s); ++s)
	{}

	if (s > str->str)
		if (!str_remove_range_unlocked(str, 0, s - str->str))
			return NULL;

	return str;
}
