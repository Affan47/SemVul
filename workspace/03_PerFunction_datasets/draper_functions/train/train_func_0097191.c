que_push(que_t *q, node_t *n)
{
	if (NULL == q || n == NULL)
	{

		return(-1);
	}


	n->next = q->list;
	q->list = n;
	q->amount++;

	if (NULL == q->tail)
	{
		q->tail = q->list;
	}


	return(0);
}
