str_substr_with_locker_unlocked(Locker *locker, const String *str, ssize_t index, ssize_t range)
{
	String *ret;

	if (!str)
		return set_errnull(EINVAL);

	if (index < 0)
		index = str->length + index;

	if (index < 0)
		return set_errnull(EINVAL);

	if (range < 0)
		range = str->length + range - index;

	if (range < 0)
		return set_errnull(EINVAL);

	if (str->length - 1 < index + range)
		return set_errnull(EINVAL);

	if (!(ret = str_create_with_locker_sized(locker, range + 1, NULL)))
		return NULL;

	memcpy(ret->str, str->str + index, range);
	ret->length = range + 1;
	ret->str[ret->length - 1] = '\0';

	return ret;
}
