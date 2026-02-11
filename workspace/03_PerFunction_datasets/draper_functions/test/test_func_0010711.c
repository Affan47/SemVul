lpfc_cleanup_vports_rrqs(struct lpfc_vport *vport, struct lpfc_nodelist *ndlp)

{
	struct lpfc_hba *phba = vport->phba;
	struct lpfc_node_rrq *rrq;
	struct lpfc_node_rrq *nextrrq;
	unsigned long iflags;
	LIST_HEAD(rrq_list);

	if (phba->sli_rev != LPFC_SLI_REV4)
		return;
	if (!ndlp) {
		lpfc_sli4_vport_delete_els_xri_aborted(vport);
		lpfc_sli4_vport_delete_fcp_xri_aborted(vport);
	}
	spin_lock_irqsave(&phba->hbalock, iflags);
	list_for_each_entry_safe(rrq, nextrrq, &phba->active_rrq_list, list)
		if ((rrq->vport == vport) && (!ndlp  || rrq->ndlp == ndlp))
			list_move(&rrq->list, &rrq_list);
	spin_unlock_irqrestore(&phba->hbalock, iflags);

	list_for_each_entry_safe(rrq, nextrrq, &rrq_list, list) {
		list_del(&rrq->list);
		lpfc_clr_rrq_active(phba, rrq->xritag, rrq);
	}
}
