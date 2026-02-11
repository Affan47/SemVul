slist_add_if_uniq(slist *l, const char *str)
{
	snode sn;
        register snode *cur;

       	cur = l->head;
	while (cur) {
		if (strcmp(str, cur->str) == 0) {
			cur->hits++;
			l->cur = cur;
			return 0;
		} else
			cur = cur->next;
	}


	sn.str = strdup(str);
	sn.key = NULL;
	sn.hits = 1;
	slist_append(l, &sn);
	return 1;
}
