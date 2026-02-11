list_add_sorted(list_t *list, void *data, int (*comparision)(void *, void *))
{
	list_t new_, tmp;

	if (!list) {
		errno = EFAULT;
		return NULL;
	}

	new_ = xmalloc(sizeof(struct list));

	new_->data = data;
	new_->next = NULL;


	if (!(tmp = *list)) {
		*list = new_;
	} else {
		if (!comparision) {
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new_;
		} else {
			list_t prev = NULL;

			while (comparision(new_->data, tmp->data) > 0) {
				prev = tmp;
				tmp = tmp->next;
				if (!tmp)
					break;
			}

			if (!prev) {
				new_->next = *list;
				*list = new_;
			} else {
				prev->next = new_;
				new_->next = tmp;
			}
		}
	}

	return new_->data;
}
