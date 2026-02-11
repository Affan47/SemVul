mraid_mm_free_adp_resources(mraid_mmadp_t *adp)
{
	uioc_t	*kioc;
	int	i;

	mraid_mm_teardown_dma_pools(adp);

	for (i = 0; i < adp->max_kioc; i++) {

		kioc = adp->kioc_list + i;

		pci_pool_free(adp->pthru_dma_pool, kioc->pthru32,
				kioc->pthru32_h);
	}

	kfree(adp->kioc_list);
	kfree(adp->mbox_list);

	pci_pool_destroy(adp->pthru_dma_pool);


	return;
}
