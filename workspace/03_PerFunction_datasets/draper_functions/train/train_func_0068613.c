trim_smf(struct smf *sp, size_t bytes)
{
	struct smf *sp2;
	struct smf_sc *sc = sp->sc;

	assert(sp->alloc != 0);
	assert(bytes > 0);
	assert(bytes < sp->size);
	assert(!(bytes % sc->pagesize));
	assert(!(sp->size % sc->pagesize));
	CHECK_OBJ_NOTNULL(sp, SMF_MAGIC);
	sp2 = malloc(sizeof *sp2);
	XXXAN(sp2);
	sc->stats->g_smf++;
	*sp2 = *sp;

	sp2->size -= bytes;
	sp->size = bytes;
	sp2->ptr += bytes;
	sp2->offset += bytes;
	VTAILQ_INSERT_AFTER(&sc->order, sp, sp2, order);
	VTAILQ_INSERT_TAIL(&sc->used, sp2, status);
	free_smf(sp2);
}
