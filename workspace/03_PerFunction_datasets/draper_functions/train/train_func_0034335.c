ipr_ata_phy_reset(struct ata_port *ap)
{
	unsigned long flags;
	struct ipr_sata_port *sata_port = ap->private_data;
	struct ipr_resource_entry *res = sata_port->res;
	struct ipr_ioa_cfg *ioa_cfg = sata_port->ioa_cfg;
	int rc;

	ENTER;
	spin_lock_irqsave(ioa_cfg->host->host_lock, flags);
	while (ioa_cfg->in_reset_reload) {
		spin_unlock_irqrestore(ioa_cfg->host->host_lock, flags);
		wait_event(ioa_cfg->reset_wait_q, !ioa_cfg->in_reset_reload);
		spin_lock_irqsave(ioa_cfg->host->host_lock, flags);
	}

	if (!ioa_cfg->hrrq[IPR_INIT_HRRQ].allow_cmds)
		goto out_unlock;

	rc = ipr_device_reset(ioa_cfg, res);

	if (rc) {
		ap->link.device[0].class = ATA_DEV_NONE;
		goto out_unlock;
	}

	ap->link.device[0].class = res->ata_class;
	if (ap->link.device[0].class == ATA_DEV_UNKNOWN)
		ap->link.device[0].class = ATA_DEV_NONE;

out_unlock:
	spin_unlock_irqrestore(ioa_cfg->host->host_lock, flags);
	LEAVE;
}
