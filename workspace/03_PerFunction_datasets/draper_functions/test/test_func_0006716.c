sil24_post_internal_cmd(struct ata_queued_cmd *qc)
{
	struct ata_port *ap = qc->ap;


	if ((qc->flags & ATA_QCFLAG_FAILED) && sil24_init_port(ap))
		ata_eh_freeze_port(ap);
}
