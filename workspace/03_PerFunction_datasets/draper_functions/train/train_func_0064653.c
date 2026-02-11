plist_append(conf_llist *l, plugin_conf_t *p)
{
	lnode* newnode;

	newnode = malloc(sizeof(lnode));

	if (p) {
		void *pp = malloc(sizeof(struct plugin_conf));
		if (pp)
			memcpy(pp, p, sizeof(struct plugin_conf));
		newnode->p = pp;
	} else
		newnode->p = NULL;

	newnode->next = 0;


	if (l->head == NULL)
		l->head = newnode;
	else
		l->cur->next = newnode;


	l->cur = newnode;
	l->cnt++;
}
