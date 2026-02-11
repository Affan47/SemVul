q_del(struct queue *q, struct entry *e)
{
	l_del(q->es, q->qs + e->level, e);
	if (!e->sentinel)
		q->nr_elts--;
}
