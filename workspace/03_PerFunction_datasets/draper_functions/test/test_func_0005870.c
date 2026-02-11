ilist_append(ilist *l, int num, unsigned int hits, int aux)
{
	int_node* newnode;

	newnode = malloc(sizeof(int_node));

	newnode->num = num;
	newnode->hits = hits;
	newnode->aux1 = aux;
	newnode->next = NULL;


	if (l->head == NULL)
		l->head = newnode;
	else
		l->cur->next = newnode;


	l->cur = newnode;
	l->cnt++;
}
