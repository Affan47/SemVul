lpfc_sli_resume_iocb(struct lpfc_hba *phba, struct lpfc_sli_ring *pring)
{
	IOCB_t *iocb;
	struct lpfc_iocbq *nextiocb;


	if (lpfc_is_link_up(phba) &&
	    (!list_empty(&pring->txq)) &&
	    (pring->ringno != phba->sli.fcp_ring ||
	     phba->sli.sli_flag & LPFC_PROCESS_LA)) {

		while ((iocb = lpfc_sli_next_iocb_slot(phba, pring)) &&
		       (nextiocb = lpfc_sli_ringtx_get(phba, pring)))
			lpfc_sli_submit_iocb(phba, pring, iocb, nextiocb);

		if (iocb)
			lpfc_sli_update_ring(phba, pring);
		else
			lpfc_sli_update_full_ring(phba, pring);
	}

	return;
}
