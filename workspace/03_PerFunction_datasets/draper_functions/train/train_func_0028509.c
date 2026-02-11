mvs_64xx_make_prd(struct scatterlist *scatter, int nr, void *prd)
{
	int i;
	struct scatterlist *sg;
	struct mvs_prd *buf_prd = prd;
	for_each_sg(scatter, sg, nr, i) {
		buf_prd->addr = cpu_to_le64(sg_dma_address(sg));
		buf_prd->len = cpu_to_le32(sg_dma_len(sg));
		buf_prd++;
	}
}
