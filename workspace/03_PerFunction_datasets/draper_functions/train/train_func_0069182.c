lpfc_mem_free(struct lpfc_hba *phba)
{
	int i;
	struct lpfc_dma_pool *pool = &phba->lpfc_mbuf_safety_pool;
	struct lpfc_device_data *device_data;


	lpfc_sli_hbqbuf_free_all(phba);
	if (phba->lpfc_drb_pool)
		pci_pool_destroy(phba->lpfc_drb_pool);
	phba->lpfc_drb_pool = NULL;
	if (phba->lpfc_hrb_pool)
		pci_pool_destroy(phba->lpfc_hrb_pool);
	phba->lpfc_hrb_pool = NULL;

	if (phba->lpfc_hbq_pool)
		pci_pool_destroy(phba->lpfc_hbq_pool);
	phba->lpfc_hbq_pool = NULL;
	mempool_destroy(phba->rrq_pool);
	phba->rrq_pool = NULL;


	mempool_destroy(phba->nlp_mem_pool);
	phba->nlp_mem_pool = NULL;
	if (phba->sli_rev == LPFC_SLI_REV4) {
		mempool_destroy(phba->active_rrq_pool);
		phba->active_rrq_pool = NULL;
	}


	mempool_destroy(phba->mbox_mem_pool);
	phba->mbox_mem_pool = NULL;


	for (i = 0; i < pool->current_count; i++)
		pci_pool_free(phba->lpfc_mbuf_pool, pool->elements[i].virt,
			      pool->elements[i].phys);
	kfree(pool->elements);

	pci_pool_destroy(phba->lpfc_mbuf_pool);
	phba->lpfc_mbuf_pool = NULL;


	pci_pool_destroy(phba->lpfc_scsi_dma_buf_pool);
	phba->lpfc_scsi_dma_buf_pool = NULL;


	if (phba->device_data_mem_pool) {

		while (!list_empty(&phba->luns)) {
			device_data = list_first_entry(&phba->luns,
						       struct lpfc_device_data,
						       listentry);
			list_del(&device_data->listentry);
			mempool_free(device_data, phba->device_data_mem_pool);
		}
		mempool_destroy(phba->device_data_mem_pool);
	}
	phba->device_data_mem_pool = NULL;
	return;
}
