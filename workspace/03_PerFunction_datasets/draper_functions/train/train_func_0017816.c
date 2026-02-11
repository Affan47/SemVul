lpfc_sli_hba_iocb_abort(struct lpfc_hba *phba)
{
	struct lpfc_sli *psli = &phba->sli;
	struct lpfc_sli_ring *pring;
	int i;

	for (i = 0; i < psli->num_rings; i++) {
		pring = &psli->ring[i];
		lpfc_sli_abort_iocb_ring(phba, pring);
	}
}
