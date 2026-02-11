slist_append(slist *l, snode *node)
{
	snode* newnode;

	newnode = malloc(sizeof(snode));

	if (node->str)
		newnode->str = node->str;
	else
		newnode->str = NULL;

	if (node->key)
		newnode->key = node->key;
	else
		newnode->key = NULL;

	newnode->hits = node->hits;
	newnode->next = NULL;


	slist_last(l);


	if (l->head == NULL)
		l->head = newnode;
	else
		l->cur->next = newnode;


	l->cur = newnode;
	l->cnt++;
}
