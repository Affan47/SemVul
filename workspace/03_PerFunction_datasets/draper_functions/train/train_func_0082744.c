tls_cache_add(struct CACHE *p, const char *val, size_t vallen)
{
	int rc;

	if (p->fd < 0)
		return (0);

	if (ll_lock_ex(p->fd) < 0)
	{
		close(p->fd);
		p->fd= -1;
		return (-1);
	}

	rc=doadd(p, val, vallen);

	if (rc < 0 && p->fd >= 0)
	{
		close(p->fd);
		p->fd= -1;
		unlink(p->filename);
		perror("ALERT: tlscache.c: ");
		fprintf(stderr, "ALERT: tlscache.c: removing %s\n",
			p->filename);
	}

	if (p->fd >= 0 && ll_unlock_ex(p->fd) < 0)
	{
		close(p->fd);
		p->fd= -1;
		rc= -1;
	}

	if (rc != 0)
		rc= -1;

	return rc;
}
