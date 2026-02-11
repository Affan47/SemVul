cleanup_add(struct cleanup *clup, void (*f)(void *), void *handler)
{
	struct cleanupq *cq;

	if ((cq = malloc(sizeof(*cq))) == NULL)
		return (-1);

	cq->f = f;
	cq->handler = handler;

	TAILQ_INSERT_HEAD(&clup->head, cq, next);

	return (0);
}
