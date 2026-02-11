dlist_reverse(dlist *l)
{
	dlist *iter1 = dlist_first(l),
		*iter2 = dlist_last(l);

	while(iter1 != iter2) {
		dlist_swap(iter1, iter2);
		if(iter1->next == iter2)
			break;
		iter1 = iter1->next;
		iter2 = iter2->prev;
	}
}
