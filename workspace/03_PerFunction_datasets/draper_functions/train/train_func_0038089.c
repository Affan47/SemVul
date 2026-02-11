HISclose(struct history *h)
{
    bool r;

    if (his_checknull(h))
	return false;
    r = (*h->methods->close)(h->sub);
    if (h->cache) {
	free(h->cache);
	h->cache = NULL;
    }
    if (h->error) {
	free((void *)h->error);
	h->error = NULL;
    }
    free(h);
    return r;
}
