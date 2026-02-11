list_disown_unlocked(List *list)
{
	list_release_t *destroy;

	if (!list)
		return (list_release_t *)set_errnullf(EINVAL);

	destroy = list->destroy;
	list->destroy = NULL;

	return destroy;
}
