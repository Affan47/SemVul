lpfc_cancel_retry_delay_tmo(struct lpfc_vport *vport, struct lpfc_nodelist *nlp)
{
	struct Scsi_Host *shost = lpfc_shost_from_vport(vport);
	struct lpfc_work_evt *evtp;

	if (!(nlp->nlp_flag & NLP_DELAY_TMO))
		return;
	spin_lock_irq(shost->host_lock);
	nlp->nlp_flag &= ~NLP_DELAY_TMO;
	spin_unlock_irq(shost->host_lock);
	del_timer_sync(&nlp->nlp_delayfunc);
	nlp->nlp_last_elscmd = 0;
	if (!list_empty(&nlp->els_retry_evt.evt_listp)) {
		list_del_init(&nlp->els_retry_evt.evt_listp);

		evtp = &nlp->els_retry_evt;
		lpfc_nlp_put((struct lpfc_nodelist *)evtp->evt_arg1);
	}
	if (nlp->nlp_flag & NLP_NPR_2B_DISC) {
		spin_lock_irq(shost->host_lock);
		nlp->nlp_flag &= ~NLP_NPR_2B_DISC;
		spin_unlock_irq(shost->host_lock);
		if (vport->num_disc_nodes) {
			if (vport->port_state < LPFC_VPORT_READY) {

				lpfc_more_adisc(vport);
			} else {

				lpfc_more_plogi(vport);
				if (vport->num_disc_nodes == 0) {
					spin_lock_irq(shost->host_lock);
					vport->fc_flag &= ~FC_NDISC_ACTIVE;
					spin_unlock_irq(shost->host_lock);
					lpfc_can_disctmo(vport);
					lpfc_end_rscn(vport);
				}
			}
		}
	}
	return;
}
