fsl_edma_alloc_desc(struct fsl_edma_chan *fsl_chan,
		int sg_len)
{
	struct fsl_edma_desc *fsl_desc;
	int i;

	fsl_desc = kzalloc(sizeof(*fsl_desc) + sizeof(struct fsl_edma_sw_tcd) * sg_len,
				GFP_NOWAIT);
	if (!fsl_desc)
		return NULL;

	fsl_desc->echan = fsl_chan;
	fsl_desc->n_tcds = sg_len;
	for (i = 0; i < sg_len; i++) {
		fsl_desc->tcd[i].vtcd = dma_pool_alloc(fsl_chan->tcd_pool,
					GFP_NOWAIT, &fsl_desc->tcd[i].ptcd);
		if (!fsl_desc->tcd[i].vtcd)
			goto err;
	}
	return fsl_desc;

err:
	while (--i >= 0)
		dma_pool_free(fsl_chan->tcd_pool, fsl_desc->tcd[i].vtcd,
				fsl_desc->tcd[i].ptcd);
	kfree(fsl_desc);
	return NULL;
}
