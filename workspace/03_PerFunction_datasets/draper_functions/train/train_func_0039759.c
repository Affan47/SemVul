list_destroy2(list_t list, void (*func)(void *)) {
	list_t tmp;

	while (list) {
		if (func && list->data)
			func(list->data);

		tmp = list->next;

		xfree(list);

		list = tmp;
	}

	return 0;
}
