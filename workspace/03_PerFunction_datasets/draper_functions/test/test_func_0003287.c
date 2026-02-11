pool_cut(struct mempool_t* p, size_t off, size_t s)
{
	pthread_mutex_lock(&p->lock);
	if (!s || (off + s > p->data_size))
		goto out;

	memmove(p->base + off, p->base + off + s, p->data_size - off - s);
	pool_resize(p, p->data_size - s);
out:
	pthread_mutex_unlock(&p->lock);
}
