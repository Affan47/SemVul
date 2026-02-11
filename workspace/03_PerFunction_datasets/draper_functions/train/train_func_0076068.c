fotg210_mem_cleanup(struct fotg210_hcd *fotg210)
{
	if (fotg210->async)
		qh_destroy(fotg210, fotg210->async);
	fotg210->async = NULL;

	if (fotg210->dummy)
		qh_destroy(fotg210, fotg210->dummy);
	fotg210->dummy = NULL;


	dma_pool_destroy(fotg210->qtd_pool);
	fotg210->qtd_pool = NULL;

	dma_pool_destroy(fotg210->qh_pool);
	fotg210->qh_pool = NULL;

	dma_pool_destroy(fotg210->itd_pool);
	fotg210->itd_pool = NULL;

	if (fotg210->periodic)
		dma_free_coherent(fotg210_to_hcd(fotg210)->self.controller,
				fotg210->periodic_size * sizeof(u32),
				fotg210->periodic, fotg210->periodic_dma);
	fotg210->periodic = NULL;


	kfree(fotg210->pshadow);
	fotg210->pshadow = NULL;
}
