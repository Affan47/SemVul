lpfc_device_rm_prli_issue(struct lpfc_vport *vport, struct lpfc_nodelist *ndlp,
			  void *arg, uint32_t evt)
{
	struct Scsi_Host *shost = lpfc_shost_from_vport(vport);

	if (ndlp->nlp_flag & NLP_NPR_2B_DISC) {
		spin_lock_irq(shost->host_lock);
		ndlp->nlp_flag |= NLP_NODEV_REMOVE;
		spin_unlock_irq(shost->host_lock);
		return ndlp->nlp_state;
	} else {

		lpfc_els_abort(vport->phba, ndlp);

		lpfc_drop_node(vport, ndlp);
		return NLP_STE_FREED_NODE;
	}
}
