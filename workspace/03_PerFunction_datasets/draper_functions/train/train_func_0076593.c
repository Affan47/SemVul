rdu_buf_lock(int fd)
{
	struct rdu *p;
	int i;

	assert(rdu);
	assert(fd >= 0);

	p = NULL;
	rdu_lib_lock();
	for (i = 0; i < rdu_cur; i++)
		if (rdu[i] && rdu[i]->fd == fd) {
			p = rdu[i];
			goto out;
		}

	for (i = 0; i < rdu_cur; i++)
		if (rdu[i] && rdu[i]->fd == -1) {
			p = rdu[i];
			p->fd = fd;
			goto out;
		}
	if (!p)
		p = rdu_new(fd);

 out:
	rdu_lib_unlock();
	if (p) {
		rdu_write_lock(p);
		if (p->fd < 0) {
			rdu_unlock(p);
			p = NULL;
		}
	}

	return p;
}
