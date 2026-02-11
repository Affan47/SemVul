arasan_cf_qc_issue(struct ata_queued_cmd *qc)
{
	struct ata_port *ap = qc->ap;
	struct arasan_cf_dev *acdev = ap->host->private_data;


	if (!ata_is_dma(qc->tf.protocol))
		return ata_sff_qc_issue(qc);


	ata_wait_idle(ap);
	ata_sff_dev_select(ap, qc->dev->devno);
	ata_wait_idle(ap);


	switch (qc->tf.protocol) {
	case ATA_PROT_DMA:
		WARN_ON_ONCE(qc->tf.flags & ATA_TFLAG_POLLING);

		ap->ops->sff_tf_load(ap, &qc->tf);
		acdev->dma_status = 0;
		acdev->qc = qc;
		arasan_cf_dma_start(acdev);
		ap->hsm_task_state = HSM_ST_LAST;
		break;

	default:
		WARN_ON(1);
		return AC_ERR_SYSTEM;
	}

	return 0;
}
