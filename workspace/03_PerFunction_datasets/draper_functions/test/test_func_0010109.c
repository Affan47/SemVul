nv_swncq_issue_atacmd(struct ata_port *ap,
					  struct ata_queued_cmd *qc)
{
	struct nv_swncq_port_priv *pp = ap->private_data;

	if (qc == NULL)
		return 0;

	DPRINTK("Enter\n");

	writel((1 << qc->tag), pp->sactive_block);
	pp->last_issue_tag = qc->tag;
	pp->dhfis_bits &= ~(1 << qc->tag);
	pp->dmafis_bits &= ~(1 << qc->tag);
	pp->qc_active |= (0x1 << qc->tag);

	ap->ops->sff_tf_load(ap, &qc->tf);
	ap->ops->sff_exec_command(ap, &qc->tf);

	DPRINTK("Issued tag %u\n", qc->tag);

	return 0;
}
