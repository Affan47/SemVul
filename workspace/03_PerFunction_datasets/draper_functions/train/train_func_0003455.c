__alloc_tpd(struct he_dev *he_dev)
{
	struct he_tpd *tpd;
	dma_addr_t mapping;

	tpd = dma_pool_alloc(he_dev->tpd_pool, GFP_ATOMIC, &mapping);
	if (tpd == NULL)
		return NULL;

	tpd->status = TPD_ADDR(mapping);
	tpd->reserved = 0;
	tpd->iovec[0].addr = 0; tpd->iovec[0].len = 0;
	tpd->iovec[1].addr = 0; tpd->iovec[1].len = 0;
	tpd->iovec[2].addr = 0; tpd->iovec[2].len = 0;

	return tpd;
}
