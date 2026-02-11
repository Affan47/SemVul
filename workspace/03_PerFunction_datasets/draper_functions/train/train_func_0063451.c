zcomp_strm_alloc(struct zcomp *comp)
{
	struct zcomp_strm *zstrm = kmalloc(sizeof(*zstrm), GFP_NOIO);
	if (!zstrm)
		return NULL;

	zstrm->private = comp->backend->create();


	zstrm->buffer = (void *)__get_free_pages(GFP_NOIO | __GFP_ZERO, 1);
	if (!zstrm->private || !zstrm->buffer) {
		zcomp_strm_free(comp, zstrm);
		zstrm = NULL;
	}
	return zstrm;
}
