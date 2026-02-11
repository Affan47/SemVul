inic_qc_prep(struct ata_queued_cmd *qc)
{
	struct inic_port_priv *pp = qc->ap->private_data;
	struct inic_pkt *pkt = pp->pkt;
	struct inic_cpb *cpb = &pkt->cpb;
	struct inic_prd *prd = pkt->prd;
	bool is_atapi = ata_is_atapi(qc->tf.protocol);
	bool is_data = ata_is_data(qc->tf.protocol);
	unsigned int cdb_len = 0;

	VPRINTK("ENTER\n");

	if (is_atapi)
		cdb_len = qc->dev->cdb_len;


	memset(pkt, 0, sizeof(struct inic_pkt));

	cpb->ctl_flags = CPB_CTL_VALID | CPB_CTL_IEN;
	if (is_atapi || is_data)
		cpb->ctl_flags |= CPB_CTL_DATA;

	cpb->len = cpu_to_le32(qc->nbytes + cdb_len);
	cpb->prd = cpu_to_le32(pp->pkt_dma + offsetof(struct inic_pkt, prd));

	cpb->device = qc->tf.device;
	cpb->feature = qc->tf.feature;
	cpb->nsect = qc->tf.nsect;
	cpb->lbal = qc->tf.lbal;
	cpb->lbam = qc->tf.lbam;
	cpb->lbah = qc->tf.lbah;

	if (qc->tf.flags & ATA_TFLAG_LBA48) {
		cpb->hob_feature = qc->tf.hob_feature;
		cpb->hob_nsect = qc->tf.hob_nsect;
		cpb->hob_lbal = qc->tf.hob_lbal;
		cpb->hob_lbam = qc->tf.hob_lbam;
		cpb->hob_lbah = qc->tf.hob_lbah;
	}

	cpb->command = qc->tf.command;


	if (is_atapi) {
		memcpy(pkt->cdb, qc->cdb, ATAPI_CDB_LEN);
		prd->mad = cpu_to_le32(pp->pkt_dma +
				       offsetof(struct inic_pkt, cdb));
		prd->len = cpu_to_le16(cdb_len);
		prd->flags = PRD_CDB | PRD_WRITE;
		if (!is_data)
			prd->flags |= PRD_END;
		prd++;
	}


	if (is_data)
		inic_fill_sg(prd, qc);

	pp->cpb_tbl[0] = pp->pkt_dma;
}
