str_insert_str_unlocked(String *str, ssize_t index, const String *src)
{
	size_t length;

	if (!str || !src)
		return set_errnull(EINVAL);

	if (index < 0)
		index = str->length + index;

	if (index < 0)
		return set_errnull(EINVAL);

	if (str->length - 1 < index)
		return set_errnull(EINVAL);

	length = src->length - 1;

	if (expand(str, index, length) == -1)
		return NULL;

	memcpy(str->str + index, src->str, length);

	return str;
}
