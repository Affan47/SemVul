lpfc_get_node_by_target(struct scsi_target *starget)
{
	struct Scsi_Host  *shost = dev_to_shost(starget->dev.parent);
	struct lpfc_vport *vport = (struct lpfc_vport *) shost->hostdata;
	struct lpfc_nodelist *ndlp;

	spin_lock_irq(shost->host_lock);

	list_for_each_entry(ndlp, &vport->fc_nodes, nlp_listp) {
		if (NLP_CHK_NODE_ACT(ndlp) &&
		    ndlp->nlp_state == NLP_STE_MAPPED_NODE &&
		    starget->id == ndlp->nlp_sid) {
			spin_unlock_irq(shost->host_lock);
			return ndlp;
		}
	}
	spin_unlock_irq(shost->host_lock);
	return NULL;
}
