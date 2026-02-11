remove_group(LIST *list, GROUP *group)
{
    GROUP *prev, *tmp;

    prev = NULL;
    for (tmp = list->head; tmp; tmp = tmp->next) {
	if (tmp == group)
	    break;
	prev = tmp;
    }

    if (!tmp) {
	logit(L_BOTH, "ERROR: remove_group can't find group");
	return;
    }

    if (!prev)
	list->head = group->next;
    else
	prev->next = group->next;

    if (!group->next)
	list->tail = prev;

    list->length--;


}
