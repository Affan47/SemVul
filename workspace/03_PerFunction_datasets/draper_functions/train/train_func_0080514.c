kmod_config_iter_next(struct kmod_config_iter *iter)
{
	if (iter == NULL)
		return false;

	if (iter->curr == NULL) {
		iter->curr = iter->list;
		return iter->curr != NULL;
	}

	iter->curr = kmod_list_next(iter->list, iter->curr);

	return iter->curr != NULL;
}
