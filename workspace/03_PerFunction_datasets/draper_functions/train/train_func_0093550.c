queue_path(struct fuse *f, struct lock_queue_element *qe)
{
	struct lock_queue_element **qp;

	qe->done = false;
	qe->first_locked = false;
	qe->second_locked = false;
	pthread_cond_init(&qe->cond, NULL);
	qe->next = NULL;
	for (qp = &f->lockq; *qp != NULL; qp = &(*qp)->next);
	*qp = qe;
}
