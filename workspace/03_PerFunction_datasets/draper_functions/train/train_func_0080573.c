dico_iterator_detach(dico_iterator_t iter)
{
    dico_iterator_t cur, prev;

    for (cur = iter->list->itr, prev = NULL;
	 cur;
	 prev = cur, cur = cur->next)
	if (cur == iter)
	    break;

    if (cur) {
	if (prev)
	    prev->next = cur->next;
	else
	    cur->list->itr = cur->next;
    }
    return cur;
}
