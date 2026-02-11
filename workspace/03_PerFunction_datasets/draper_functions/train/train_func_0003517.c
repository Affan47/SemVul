lpfc_device_recov_adisc_issue(struct lpfc_vport *vport,
			      struct lpfc_nodelist *ndlp,
			      void *arg,
			      uint32_t evt)
{
	struct Scsi_Host *shost = lpfc_shost_from_vport(vport);
	struct lpfc_hba  *phba = vport->phba;


	if (vport->fc_flag & FC_RSCN_DEFERRED)
		return ndlp->nlp_state;


	lpfc_els_abort(phba, ndlp);

	ndlp->nlp_prev_state = NLP_STE_ADISC_ISSUE;
	lpfc_nlp_set_state(vport, ndlp, NLP_STE_NPR_NODE);
	spin_lock_irq(shost->host_lock);
	ndlp->nlp_flag &= ~(NLP_NODEV_REMOVE | NLP_NPR_2B_DISC);
	spin_unlock_irq(shost->host_lock);
	lpfc_disc_set_adisc(vport, ndlp);
	return ndlp->nlp_state;
}
