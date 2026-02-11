qdi_qc_issue(struct ata_queued_cmd *qc)
{
	struct ata_port *ap = qc->ap;
	struct ata_device *adev = qc->dev;
	struct legacy_data *ld_qdi = ap->host->private_data;

	if (ld_qdi->clock[adev->devno] != ld_qdi->last) {
		if (adev->pio_mode) {
			ld_qdi->last = ld_qdi->clock[adev->devno];
			outb(ld_qdi->clock[adev->devno], ld_qdi->timing +
							2 * ap->port_no);
		}
	}
	return ata_sff_qc_issue(qc);
}
