_k_insert_after(K_LIST *list, K_ITEM *item, K_ITEM *after, KLIST_FFL_ARGS)
{
	if (item->name != list->name) {
		quithere(1, "List %s can't %s() a %s item" KLIST_FFL,
				list->name, __func__, item->name, KLIST_FFL_PASS);
	}

	if (!after) {
		quithere(1, "%s() (%s) can't after a null item" KLIST_FFL,
				__func__, list->name, KLIST_FFL_PASS);
	}

	item->prev = after;
	item->next = after->next;
	if (after->next)
		after->next->prev = item;
	else {
		if (list->do_tail)
			list->tail = item;
	}
	after->next = item;

	list->count++;
	list->count_up++;
}
