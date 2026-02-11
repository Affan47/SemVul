lpfc_dump_wakeup_param_cmpl(struct lpfc_hba *phba, LPFC_MBOXQ_t *pmboxq)
{
	struct prog_id *prg;
	uint32_t prog_id_word;
	char dist = ' ';

	char dist_char[] = "nabx";

	if (pmboxq->u.mb.mbxStatus != MBX_SUCCESS) {
		mempool_free(pmboxq, phba->mbox_mem_pool);
		return;
	}

	prg = (struct prog_id *) &prog_id_word;


	prog_id_word = pmboxq->u.mb.un.varWords[7];


	if (prg->dist < 4)
		dist = dist_char[prg->dist];

	if ((prg->dist == 3) && (prg->num == 0))
		snprintf(phba->OptionROMVersion, 32, "%d.%d%d",
			prg->ver, prg->rev, prg->lev);
	else
		snprintf(phba->OptionROMVersion, 32, "%d.%d%d%c%d",
			prg->ver, prg->rev, prg->lev,
			dist, prg->num);
	mempool_free(pmboxq, phba->mbox_mem_pool);
	return;
}
