lpfc_delayed_disc_timeout_handler(struct lpfc_vport *vport)
{
	struct Scsi_Host *shost = lpfc_shost_from_vport(vport);

	spin_lock_irq(shost->host_lock);
	if (!(vport->fc_flag & FC_DISC_DELAYED)) {
		spin_unlock_irq(shost->host_lock);
		return;
	}
	vport->fc_flag &= ~FC_DISC_DELAYED;
	spin_unlock_irq(shost->host_lock);

	lpfc_do_scr_ns_plogi(vport->phba, vport);
}
