lpfcdiag_loop_self_reg(struct lpfc_hba *phba, uint16_t *rpi)
{
	LPFC_MBOXQ_t *mbox;
	struct lpfc_dmabuf *dmabuff;
	int status;

	mbox = mempool_alloc(phba->mbox_mem_pool, GFP_KERNEL);
	if (!mbox)
		return -ENOMEM;

	if (phba->sli_rev < LPFC_SLI_REV4)
		status = lpfc_reg_rpi(phba, 0, phba->pport->fc_myDID,
				(uint8_t *)&phba->pport->fc_sparam,
				mbox, *rpi);
	else {
		*rpi = lpfc_sli4_alloc_rpi(phba);
		status = lpfc_reg_rpi(phba, phba->pport->vpi,
				phba->pport->fc_myDID,
				(uint8_t *)&phba->pport->fc_sparam,
				mbox, *rpi);
	}

	if (status) {
		mempool_free(mbox, phba->mbox_mem_pool);
		if (phba->sli_rev == LPFC_SLI_REV4)
			lpfc_sli4_free_rpi(phba, *rpi);
		return -ENOMEM;
	}

	dmabuff = (struct lpfc_dmabuf *) mbox->context1;
	mbox->context1 = NULL;
	mbox->context2 = NULL;
	status = lpfc_sli_issue_mbox_wait(phba, mbox, LPFC_MBOX_TMO);

	if ((status != MBX_SUCCESS) || (mbox->u.mb.mbxStatus)) {
		lpfc_mbuf_free(phba, dmabuff->virt, dmabuff->phys);
		kfree(dmabuff);
		if (status != MBX_TIMEOUT)
			mempool_free(mbox, phba->mbox_mem_pool);
		if (phba->sli_rev == LPFC_SLI_REV4)
			lpfc_sli4_free_rpi(phba, *rpi);
		return -ENODEV;
	}

	if (phba->sli_rev < LPFC_SLI_REV4)
		*rpi = mbox->u.mb.un.varWords[0];

	lpfc_mbuf_free(phba, dmabuff->virt, dmabuff->phys);
	kfree(dmabuff);
	mempool_free(mbox, phba->mbox_mem_pool);
	return 0;
}
