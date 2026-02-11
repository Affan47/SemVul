push(Object *obj)
{
	Queuenode	*node = new Queuenode;

	node->obj = obj;
	node->next = 0;
	if (tail)
		((Queuenode *) tail)->next = node;
	tail = node;
	if (!head)
		head = tail;
	size++;
}
