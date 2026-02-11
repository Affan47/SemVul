list_append(llist *l, lnode *node)
{
	lnode* newnode;

	newnode = malloc(sizeof(lnode));

	newnode->sec = node->sec;
	newnode->uid = node->uid;
	newnode->name = strdup(node->name);
	if (node->host)
		newnode->host = strdup(node->host);
	else
		newnode->host = NULL;
	if (node->term)
		newnode->term = strdup(node->term);
	else
		newnode->term = NULL;
	newnode->item = l->cnt;
	newnode->next = NULL;


	if (l->head == NULL)
		l->head = newnode;
	else
		l->cur->next = newnode;


	l->cur = newnode;
	l->cnt++;
}
