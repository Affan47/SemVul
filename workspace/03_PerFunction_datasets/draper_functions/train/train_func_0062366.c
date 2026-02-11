lpfc_modify_fcp_eq_delay(struct lpfc_hba *phba, uint32_t startq)
{
	struct lpfc_mbx_modify_eq_delay *eq_delay;
	LPFC_MBOXQ_t *mbox;
	struct lpfc_queue *eq;
	int cnt, rc, length, status = 0;
	uint32_t shdr_status, shdr_add_status;
	uint32_t result;
	int fcp_eqidx;
	union lpfc_sli4_cfg_shdr *shdr;
	uint16_t dmult;

	if (startq >= phba->cfg_fcp_io_channel)
		return 0;

	mbox = mempool_alloc(phba->mbox_mem_pool, GFP_KERNEL);
	if (!mbox)
		return -ENOMEM;
	length = (sizeof(struct lpfc_mbx_modify_eq_delay) -
		  sizeof(struct lpfc_sli4_cfg_mhdr));
	lpfc_sli4_config(phba, mbox, LPFC_MBOX_SUBSYSTEM_COMMON,
			 LPFC_MBOX_OPCODE_MODIFY_EQ_DELAY,
			 length, LPFC_SLI4_MBX_EMBED);
	eq_delay = &mbox->u.mqe.un.eq_delay;


	result = phba->cfg_fcp_imax / phba->cfg_fcp_io_channel;
	if (result > LPFC_DMULT_CONST)
		dmult = 0;
	else
		dmult = LPFC_DMULT_CONST/result - 1;

	cnt = 0;
	for (fcp_eqidx = startq; fcp_eqidx < phba->cfg_fcp_io_channel;
	    fcp_eqidx++) {
		eq = phba->sli4_hba.hba_eq[fcp_eqidx];
		if (!eq)
			continue;
		eq_delay->u.request.eq[cnt].eq_id = eq->queue_id;
		eq_delay->u.request.eq[cnt].phase = 0;
		eq_delay->u.request.eq[cnt].delay_multi = dmult;
		cnt++;
		if (cnt >= LPFC_MAX_EQ_DELAY)
			break;
	}
	eq_delay->u.request.num_eq = cnt;

	mbox->vport = phba->pport;
	mbox->mbox_cmpl = lpfc_sli_def_mbox_cmpl;
	mbox->context1 = NULL;
	rc = lpfc_sli_issue_mbox(phba, mbox, MBX_POLL);
	shdr = (union lpfc_sli4_cfg_shdr *) &eq_delay->header.cfg_shdr;
	shdr_status = bf_get(lpfc_mbox_hdr_status, &shdr->response);
	shdr_add_status = bf_get(lpfc_mbox_hdr_add_status, &shdr->response);
	if (shdr_status || shdr_add_status || rc) {
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"2512 MODIFY_EQ_DELAY mailbox failed with "
				"status x%x add_status x%x, mbx status x%x\n",
				shdr_status, shdr_add_status, rc);
		status = -ENXIO;
	}
	mempool_free(mbox, phba->mbox_mem_pool);
	return status;
}
