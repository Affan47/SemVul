gfs_xmlattr_ctx_alloc(int nentry)
{
	struct gfs_xmlattr_ctx *ctxp;
	size_t ctxsize;
	int overflow;
	char *p = NULL;

	overflow = 0;
	ctxsize = gfarm_size_add(&overflow, sizeof(*ctxp),
			gfarm_size_mul(&overflow, nentry, sizeof(*ctxp->entries)));
	if (!overflow)
		p = calloc(1, ctxsize);
	if (p != NULL) {
		ctxp = (struct gfs_xmlattr_ctx *)p;
		ctxp->nalloc = nentry;
		ctxp->entries = (struct gfs_foundxattr_entry *)(ctxp + 1);
		return ctxp;
	} else
		return NULL;
}
