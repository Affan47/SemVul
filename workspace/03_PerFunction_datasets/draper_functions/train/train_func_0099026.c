dbq_wait_to_finish(struct dbq *q)
{
	static const char diag[] = "dbq_wait_to_finish";

	gfarm_mutex_lock(&q->mutex, diag, "mutex");
	q->quitting = 1;
	while (!q->quited) {
		gfarm_cond_signal(&q->nonempty, diag, "nonempty");
		gfarm_cond_wait(&q->finished, &q->mutex, diag, "finished");
	}
	gfarm_mutex_unlock(&q->mutex, diag, "mutex");
	return (GFARM_ERR_NO_ERROR);
}
