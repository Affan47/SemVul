lpfc_delayed_disc_tmo(unsigned long ptr)
{
	struct lpfc_vport *vport = (struct lpfc_vport *)ptr;
	struct lpfc_hba   *phba = vport->phba;
	uint32_t tmo_posted;
	unsigned long iflag;

	spin_lock_irqsave(&vport->work_port_lock, iflag);
	tmo_posted = vport->work_port_events & WORKER_DELAYED_DISC_TMO;
	if (!tmo_posted)
		vport->work_port_events |= WORKER_DELAYED_DISC_TMO;
	spin_unlock_irqrestore(&vport->work_port_lock, iflag);

	if (!tmo_posted)
		lpfc_worker_wake_up(phba);
	return;
}
