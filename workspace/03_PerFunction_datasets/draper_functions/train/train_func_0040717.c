lpfc_device_recov_reglogin_issue(struct lpfc_vport *vport,
				 struct lpfc_nodelist *ndlp,
				 void *arg,
				 uint32_t evt)
{
	struct Scsi_Host *shost = lpfc_shost_from_vport(vport);


	if (vport->fc_flag & FC_RSCN_DEFERRED)
		return ndlp->nlp_state;

	ndlp->nlp_prev_state = NLP_STE_REG_LOGIN_ISSUE;
	lpfc_nlp_set_state(vport, ndlp, NLP_STE_NPR_NODE);
	spin_lock_irq(shost->host_lock);
	ndlp->nlp_flag |= NLP_IGNR_REG_CMPL;
	ndlp->nlp_flag &= ~(NLP_NODEV_REMOVE | NLP_NPR_2B_DISC);
	spin_unlock_irq(shost->host_lock);
	lpfc_disc_set_adisc(vport, ndlp);
	return ndlp->nlp_state;
}
