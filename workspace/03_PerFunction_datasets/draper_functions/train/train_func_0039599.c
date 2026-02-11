pm8001_chip_make_sg(struct scatterlist *scatter, int nr, void *prd)
{
	int i;
	struct scatterlist *sg;
	struct pm8001_prd *buf_prd = prd;

	for_each_sg(scatter, sg, nr, i) {
		buf_prd->addr = cpu_to_le64(sg_dma_address(sg));
		buf_prd->im_len.len = cpu_to_le32(sg_dma_len(sg));
		buf_prd->im_len.e = 0;
		buf_prd++;
	}
}
