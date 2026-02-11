nv_adma_post_internal_cmd(struct ata_queued_cmd *qc)
{
	struct nv_adma_port_priv *pp = qc->ap->private_data;

	if (pp->flags & NV_ADMA_PORT_REGISTER_MODE)
		ata_bmdma_post_internal_cmd(qc);
}
