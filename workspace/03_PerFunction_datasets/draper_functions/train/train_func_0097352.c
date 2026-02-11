slink_remove(void *link)
{
	slink_t *remove;

	if (!link)
		return set_errnull(EINVAL);

	remove = link;

	return remove->next;
}
