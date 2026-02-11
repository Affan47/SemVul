list_unlink3(list_t *list, list_t elem) {
	list_t tmp, last = NULL;
	void *ret = NULL;

	tmp = *list;
	if (tmp && tmp == elem) {
		*list = ret = tmp->next;
	} else {
		for (; tmp && tmp != elem; tmp = tmp->next)
			last = tmp;
		if (!tmp) {
			errno = ENOENT;
			return ret;
		}
		last->next = ret = tmp->next;
	}

	return ret;
}
