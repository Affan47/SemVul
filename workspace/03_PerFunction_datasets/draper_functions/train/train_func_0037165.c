dequeue(nodequeue * q)
{
    node_t *n;
    if (q->head == q->tail)
	n = NULL;
    else {
	n = *(q->head++);
	if (q->head >= q->limit)
	    q->head = q->store;
    }
    return n;
}
