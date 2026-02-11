mv_port_free_dma_mem(struct ata_port *ap)
{
	struct mv_host_priv *hpriv = ap->host->private_data;
	struct mv_port_priv *pp = ap->private_data;
	int tag;

	if (pp->crqb) {
		dma_pool_free(hpriv->crqb_pool, pp->crqb, pp->crqb_dma);
		pp->crqb = NULL;
	}
	if (pp->crpb) {
		dma_pool_free(hpriv->crpb_pool, pp->crpb, pp->crpb_dma);
		pp->crpb = NULL;
	}


	for (tag = 0; tag < MV_MAX_Q_DEPTH; ++tag) {
		if (pp->sg_tbl[tag]) {
			if (tag == 0 || !IS_GEN_I(hpriv))
				dma_pool_free(hpriv->sg_tbl_pool,
					      pp->sg_tbl[tag],
					      pp->sg_tbl_dma[tag]);
			pp->sg_tbl[tag] = NULL;
		}
	}
}
