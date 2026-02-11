str_vinsert_unlocked(String *str, ssize_t index, const char *format, va_list args)
{
	String *tmp, *ret;

	if (!str)
		return set_errnull(EINVAL);

	if (index < 0)
		index = str->length + index;

	if (index < 0)
		return set_errnull(EINVAL);

	if (str->length - 1 < index)
		return set_errnull(EINVAL);

	if (!(tmp = str_vcreate(format, args)))
		return NULL;

	ret = str_insert_str_unlocked(str, index, tmp);
	str_release(tmp);

	return ret;
}
