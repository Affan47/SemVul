sortlist (List *list, int (*comp) (const Node *, const Node *))
{
    Node *head, *remain, *p, **array;
    int i, n;

    if (list == NULL)
	return;


    head = list->list;
    remain = head->next;


    n = 0;
    for (p = remain; p != head; p = p->next)
	n++;


    array = xnmalloc (n, sizeof (Node *));
    i = 0;
    for (p = remain; p != head; p = p->next)
	array[i++] = p;


    client_comp = comp;
    qsort (array, n, sizeof(Node *), qsort_comp);


    head->next = head->prev = head;
    for (i = 0; i < n; i++)
    {
	p = array[i];
	p->next = head;
	p->prev = head->prev;
	p->prev->next = p;
	head->prev = p;
    }


    free (array);
}
