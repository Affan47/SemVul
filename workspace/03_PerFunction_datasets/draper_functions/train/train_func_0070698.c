beiscsi_create_cqs(struct beiscsi_hba *phba,
			     struct hwi_context_memory *phwi_context)
{
	unsigned int i, num_cq_pages;
	int ret = 0;
	struct be_queue_info *cq, *eq;
	struct be_dma_mem *mem;
	struct be_eq_obj *pbe_eq;
	void *cq_vaddress;
	dma_addr_t paddr;

	num_cq_pages = PAGES_REQUIRED(phba->params.num_cq_entries * \
				      sizeof(struct sol_cqe));

	for (i = 0; i < phba->num_cpus; i++) {
		cq = &phwi_context->be_cq[i];
		eq = &phwi_context->be_eq[i].q;
		pbe_eq = &phwi_context->be_eq[i];
		pbe_eq->cq = cq;
		pbe_eq->phba = phba;
		mem = &cq->dma_mem;
		cq_vaddress = pci_alloc_consistent(phba->pcidev,
						     num_cq_pages * PAGE_SIZE,
						     &paddr);
		if (!cq_vaddress)
			goto create_cq_error;
		ret = be_fill_queue(cq, phba->params.num_cq_entries,
				    sizeof(struct sol_cqe), cq_vaddress);
		if (ret) {
			beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_INIT,
				    "BM_%d : be_fill_queue Failed "
				    "for ISCSI CQ\n");
			goto create_cq_error;
		}

		mem->dma = paddr;
		ret = beiscsi_cmd_cq_create(&phba->ctrl, cq, eq, false,
					    false, 0);
		if (ret) {
			beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_INIT,
				    "BM_%d : beiscsi_cmd_eq_create"
				    "Failed for ISCSI CQ\n");
			goto create_cq_error;
		}
		beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_INIT,
			    "BM_%d : iscsi cq_id is %d for eq_id %d\n"
			    "iSCSI CQ CREATED\n", cq->id, eq->id);
	}
	return 0;

create_cq_error:
	for (i = 0; i < phba->num_cpus; i++) {
		cq = &phwi_context->be_cq[i];
		mem = &cq->dma_mem;
		if (mem->va)
			pci_free_consistent(phba->pcidev, num_cq_pages
					    * PAGE_SIZE,
					    mem->va, mem->dma);
	}
	return ret;

}
