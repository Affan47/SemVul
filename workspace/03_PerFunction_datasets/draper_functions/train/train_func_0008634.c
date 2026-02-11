lpfc_sli4_abts_err_handler(struct lpfc_hba *phba,
			   struct lpfc_nodelist *ndlp,
			   struct sli4_wcqe_xri_aborted *axri)
{
	struct lpfc_vport *vport;
	uint32_t ext_status = 0;

	if (!ndlp || !NLP_CHK_NODE_ACT(ndlp)) {
		lpfc_printf_log(phba, KERN_INFO, LOG_SLI,
				"3115 Node Context not found, driver "
				"ignoring abts err event\n");
		return;
	}

	vport = ndlp->vport;
	lpfc_printf_log(phba, KERN_WARNING, LOG_SLI,
			"3116 Port generated FCP XRI ABORT event on "
			"vpi %d rpi %d xri x%x status 0x%x parameter x%x\n",
			ndlp->vport->vpi, phba->sli4_hba.rpi_ids[ndlp->nlp_rpi],
			bf_get(lpfc_wcqe_xa_xri, axri),
			bf_get(lpfc_wcqe_xa_status, axri),
			axri->parameter);


	ext_status = axri->parameter & IOERR_PARAM_MASK;
	if ((bf_get(lpfc_wcqe_xa_status, axri) == IOSTAT_LOCAL_REJECT) &&
	    ((ext_status == IOERR_SEQUENCE_TIMEOUT) || (ext_status == 0)))
		lpfc_sli_abts_recover_port(vport, ndlp);
}
