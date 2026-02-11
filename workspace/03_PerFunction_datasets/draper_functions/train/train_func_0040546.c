lpfc_release_rpi(struct lpfc_hba *phba,
		struct lpfc_vport *vport,
		uint16_t rpi)
{
	LPFC_MBOXQ_t *pmb;
	int rc;

	pmb = (LPFC_MBOXQ_t *) mempool_alloc(phba->mbox_mem_pool,
			GFP_KERNEL);
	if (!pmb)
		lpfc_printf_vlog(vport, KERN_ERR, LOG_MBOX,
			"2796 mailbox memory allocation failed \n");
	else {
		lpfc_unreg_login(phba, vport->vpi, rpi, pmb);
		pmb->mbox_cmpl = lpfc_sli_def_mbox_cmpl;
		rc = lpfc_sli_issue_mbox(phba, pmb, MBX_NOWAIT);
		if (rc == MBX_NOT_FINISHED)
			mempool_free(pmb, phba->mbox_mem_pool);
	}
}
