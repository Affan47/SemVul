lpfc_sli_next_iocb(struct lpfc_hba *phba, struct lpfc_sli_ring *pring,
		   struct lpfc_iocbq **piocb)
{
	struct lpfc_iocbq * nextiocb;

	nextiocb = lpfc_sli_ringtx_get(phba, pring);
	if (!nextiocb) {
		nextiocb = *piocb;
		*piocb = NULL;
	}

	return nextiocb;
}
