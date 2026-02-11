lpfc_initialize_node(struct lpfc_vport *vport, struct lpfc_nodelist *ndlp,
	uint32_t did)
{
	INIT_LIST_HEAD(&ndlp->els_retry_evt.evt_listp);
	INIT_LIST_HEAD(&ndlp->dev_loss_evt.evt_listp);
	init_timer(&ndlp->nlp_delayfunc);
	ndlp->nlp_delayfunc.function = lpfc_els_retry_delay;
	ndlp->nlp_delayfunc.data = (unsigned long)ndlp;
	ndlp->nlp_DID = did;
	ndlp->vport = vport;
	ndlp->phba = vport->phba;
	ndlp->nlp_sid = NLP_NO_SID;
	kref_init(&ndlp->kref);
	NLP_INT_NODE_ACT(ndlp);
	atomic_set(&ndlp->cmd_pending, 0);
	ndlp->cmd_qdepth = vport->cfg_tgt_queue_depth;
}
