lpfc_cmpl_els_prli(struct lpfc_hba *phba, struct lpfc_iocbq *cmdiocb,
		   struct lpfc_iocbq *rspiocb)
{
	struct lpfc_vport *vport = cmdiocb->vport;
	struct Scsi_Host  *shost = lpfc_shost_from_vport(vport);
	IOCB_t *irsp;
	struct lpfc_nodelist *ndlp;


	cmdiocb->context_un.rsp_iocb = rspiocb;

	irsp = &(rspiocb->iocb);
	ndlp = (struct lpfc_nodelist *) cmdiocb->context1;
	spin_lock_irq(shost->host_lock);
	ndlp->nlp_flag &= ~NLP_PRLI_SND;
	spin_unlock_irq(shost->host_lock);

	lpfc_debugfs_disc_trc(vport, LPFC_DISC_TRC_ELS_CMD,
		"PRLI cmpl:       status:x%x/x%x did:x%x",
		irsp->ulpStatus, irsp->un.ulpWord[4],
		ndlp->nlp_DID);

	lpfc_printf_vlog(vport, KERN_INFO, LOG_ELS,
			 "0103 PRLI completes to NPort x%x "
			 "Data: x%x x%x x%x x%x\n",
			 ndlp->nlp_DID, irsp->ulpStatus, irsp->un.ulpWord[4],
			 irsp->ulpTimeout, vport->num_disc_nodes);

	vport->fc_prli_sent--;

	if (lpfc_els_chk_latt(vport))
		goto out;

	if (irsp->ulpStatus) {

		if (lpfc_els_retry(phba, cmdiocb, rspiocb)) {

			goto out;
		}

		lpfc_printf_vlog(vport, KERN_ERR, LOG_ELS,
				 "2754 PRLI failure DID:%06X Status:x%x/x%x\n",
				 ndlp->nlp_DID, irsp->ulpStatus,
				 irsp->un.ulpWord[4]);

		if (lpfc_error_lost_link(irsp))
			goto out;
		else
			lpfc_disc_state_machine(vport, ndlp, cmdiocb,
						NLP_EVT_CMPL_PRLI);
	} else

		lpfc_disc_state_machine(vport, ndlp, cmdiocb,
					NLP_EVT_CMPL_PRLI);
out:
	lpfc_els_free_iocb(phba, cmdiocb);
	return;
}
