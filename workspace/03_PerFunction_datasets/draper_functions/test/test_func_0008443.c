InsertEdge(Edge *list, Edge *edge)
{
	Edge *p, *q = list;

	p = q->next;
	while (p != NULL) {
		if (edge->xIntersect < p->xIntersect) {
			p = NULL;
		}
		else {
			q = p;
			p = p->next;
		}
	}
	edge->next = q->next;
	q->next = edge;
}
