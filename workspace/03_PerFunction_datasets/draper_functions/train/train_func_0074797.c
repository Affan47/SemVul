get_buf(struct buf *b, SANE_Int * sz)
{
	SANE_Status err = buf_get_err(b);
	if (err)
		return NULL;

	pthread_mutex_lock(&b->mu);
	while (!b->sem && !buf_get_err(b))
		pthread_cond_wait(&b->cond, &b->mu);
	b->sem--;
	err = buf_get_err(b);
	if (!err) {
		*sz = b->size < BUF_SIZE ? b->size : BUF_SIZE;
		b->size -= *sz;
	}
	pthread_mutex_unlock(&b->mu);
	return err ? NULL : b->buf[b->head];
}
