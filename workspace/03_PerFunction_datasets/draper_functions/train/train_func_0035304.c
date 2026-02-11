sil_host_intr(struct ata_port *ap, u32 bmdma2)
{
	struct ata_eh_info *ehi = &ap->link.eh_info;
	struct ata_queued_cmd *qc = ata_qc_from_tag(ap, ap->link.active_tag);
	u8 status;

	if (unlikely(bmdma2 & SIL_DMA_SATA_IRQ)) {
		u32 serror = 0xffffffff;


		sil_scr_read(&ap->link, SCR_ERROR, &serror);
		sil_scr_write(&ap->link, SCR_ERROR, serror);


		if (serror & SERR_PHYRDY_CHG) {
			ap->link.eh_info.serror |= serror;
			goto freeze;
		}

		if (!(bmdma2 & SIL_DMA_COMPLETE))
			return;
	}

	if (unlikely(!qc || (qc->tf.flags & ATA_TFLAG_POLLING))) {

		ap->ops->sff_check_status(ap);
		return;
	}


	switch (ap->hsm_task_state) {
	case HSM_ST_FIRST:


		if (!(qc->dev->flags & ATA_DFLAG_CDB_INTR))
			goto err_hsm;
		break;
	case HSM_ST_LAST:
		if (ata_is_dma(qc->tf.protocol)) {

			ap->ops->bmdma_stop(qc);

			if (bmdma2 & SIL_DMA_ERROR) {
				qc->err_mask |= AC_ERR_HOST_BUS;
				ap->hsm_task_state = HSM_ST_ERR;
			}
		}
		break;
	case HSM_ST:
		break;
	default:
		goto err_hsm;
	}


	status = ap->ops->sff_check_status(ap);
	if (unlikely(status & ATA_BUSY))
		goto err_hsm;


	ata_bmdma_irq_clear(ap);


	ata_sff_hsm_move(ap, qc, status, 0);

	if (unlikely(qc->err_mask) && ata_is_dma(qc->tf.protocol))
		ata_ehi_push_desc(ehi, "BMDMA2 stat 0x%x", bmdma2);

	return;

 err_hsm:
	qc->err_mask |= AC_ERR_HSM;
 freeze:
	ata_port_freeze(ap);
}
