fdset_add(fdset_t *set, int fd, unsigned events, void *ctx)
{
	if (set == NULL || fd < 0) {
		return KNOT_EINVAL;
	}


	if (set->n == set->size && fdset_resize(set, set->size + FDSET_INIT_SIZE))
		return KNOT_ENOMEM;


	int i = set->n++;
	set->pfd[i].fd = fd;
	set->pfd[i].events = events;
	set->pfd[i].revents = 0;
	set->ctx[i] = ctx;
	set->timeout[i] = 0;


	return i;
}
