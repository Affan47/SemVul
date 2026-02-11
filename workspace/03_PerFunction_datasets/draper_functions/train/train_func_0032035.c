ib_umem_page_count(struct ib_umem *umem)
{
	int shift;
	int i;
	int n;
	struct scatterlist *sg;

	if (umem->odp_data)
		return ib_umem_num_pages(umem);

	shift = ilog2(umem->page_size);

	n = 0;
	for_each_sg(umem->sg_head.sgl, sg, umem->nmap, i)
		n += sg_dma_len(sg) >> shift;

	return n;
}
