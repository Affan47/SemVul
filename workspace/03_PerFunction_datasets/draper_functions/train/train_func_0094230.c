list_last_unlocked(const List *list)
{
	if (!list)
		return set_errno(EINVAL);

	return list->length - 1;
}
