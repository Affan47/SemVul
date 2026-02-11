lpfc_mbx_cmpl_rdp_page_a0(struct lpfc_hba *phba, LPFC_MBOXQ_t *mbox)
{
	int rc;
	struct lpfc_dmabuf *mp = (struct lpfc_dmabuf *) (mbox->context1);
	struct lpfc_rdp_context *rdp_context =
			(struct lpfc_rdp_context *)(mbox->context2);

	if (bf_get(lpfc_mqe_status, &mbox->u.mqe))
		goto error;

	lpfc_sli_bemem_bcopy(mp->virt, &rdp_context->page_a0,
				DMP_SFF_PAGE_A0_SIZE);

	memset(mbox, 0, sizeof(*mbox));

	memset(mp->virt, 0, DMP_SFF_PAGE_A2_SIZE);
	INIT_LIST_HEAD(&mp->list);


	mbox->context1 = mp;
	mbox->vport = rdp_context->ndlp->vport;

	bf_set(lpfc_mqe_command, &mbox->u.mqe, MBX_DUMP_MEMORY);
	bf_set(lpfc_mbx_memory_dump_type3_type,
		&mbox->u.mqe.un.mem_dump_type3, DMP_LMSD);
	bf_set(lpfc_mbx_memory_dump_type3_link,
		&mbox->u.mqe.un.mem_dump_type3, phba->sli4_hba.physical_port);
	bf_set(lpfc_mbx_memory_dump_type3_page_no,
		&mbox->u.mqe.un.mem_dump_type3, DMP_PAGE_A2);
	bf_set(lpfc_mbx_memory_dump_type3_length,
		&mbox->u.mqe.un.mem_dump_type3, DMP_SFF_PAGE_A2_SIZE);
	mbox->u.mqe.un.mem_dump_type3.addr_lo = putPaddrLow(mp->phys);
	mbox->u.mqe.un.mem_dump_type3.addr_hi = putPaddrHigh(mp->phys);

	mbox->mbox_cmpl = lpfc_mbx_cmpl_rdp_page_a2;
	mbox->context2 = (struct lpfc_rdp_context *) rdp_context;
	rc = lpfc_sli_issue_mbox(phba, mbox, MBX_NOWAIT);
	if (rc == MBX_NOT_FINISHED)
		goto error;

	return;

error:
	lpfc_mbuf_free(phba, mp->virt, mp->phys);
	kfree(mp);
	lpfc_sli4_mbox_cmd_free(phba, mbox);
	rdp_context->cmpl(phba, rdp_context, FAILURE);
}
