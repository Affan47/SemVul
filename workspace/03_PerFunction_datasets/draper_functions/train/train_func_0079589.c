hpt3x2n_qc_issue(struct ata_queued_cmd *qc)
{
	struct ata_port *ap = qc->ap;
	int flags = (long)ap->host->private_data;
	int dpll = hpt3x2n_use_dpll(ap, qc->tf.flags & ATA_TFLAG_WRITE);

	if ((flags & USE_DPLL) != dpll) {
		flags &= ~USE_DPLL;
		flags |= dpll;
		ap->host->private_data = (void *)(long)flags;

		hpt3x2n_set_clock(ap, dpll ? 0x21 : 0x23);
	}
	return ata_bmdma_qc_issue(qc);
}
