pqueue_insert(struct pqueue *pq, void *e)
{
	unsigned long m;
	unsigned int i;
	void *p;

	m = pq->size + 1;

	p = realloc(pq->data, m * sizeof(void *));
	if (!p)
		return -ENOMEM;
	pq->data = p;

	i = pq->size++;
	while (i > 1 && pq->compare(pq->data[i / 2], e) < 0) {
		pq->data[i] = pq->data[i / 2];
		i /= 2;
	}
	pq->data[i] = e;

	return 0;
}
