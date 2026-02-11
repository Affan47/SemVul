mergelists (List *dest, List **src)
{
    Node *head, *p, *n;

    head = (*src)->list;
    for (p = head->next; p != head; p = n)
    {
	n = p->next;
	removenode (p);
	addnode (dest, p);
    }
    dellist (src);
}
