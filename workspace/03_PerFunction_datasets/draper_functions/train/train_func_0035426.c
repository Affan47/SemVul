lpfc_ignore_els_cmpl(struct lpfc_hba *phba, struct lpfc_iocbq *cmdiocb,
		     struct lpfc_iocbq *rspiocb)
{
	IOCB_t *irsp = &rspiocb->iocb;


	lpfc_printf_log(phba, KERN_INFO, LOG_ELS,
			"0139 Ignoring ELS cmd tag x%x completion Data: "
			"x%x x%x x%x\n",
			irsp->ulpIoTag, irsp->ulpStatus,
			irsp->un.ulpWord[4], irsp->ulpTimeout);
	if (cmdiocb->iocb.ulpCommand == CMD_GEN_REQUEST64_CR)
		lpfc_ct_free_iocb(phba, cmdiocb);
	else
		lpfc_els_free_iocb(phba, cmdiocb);
	return;
}
