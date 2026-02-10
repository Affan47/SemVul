dma_map_sg_nonforce(struct device *dev, struct scatterlist *sg,
			       int nents, int dir)
{
	struct scatterlist *s;
	int i;

#ifdef CONFIG_IOMMU_DEBUG
	pr_debug("dma_map_sg overflow\n");
#endif

	for_each_sg(sg, s, nents, i) {
		unsigned long addr = sg_phys(s);

		if (nonforced_iommu(dev, addr, s->length)) {
			addr = dma_map_area(dev, addr, s->length, dir, 0);
			if (addr == bad_dma_addr) {
				if (i > 0)
					gart_unmap_sg(dev, sg, i, dir, NULL);
				nents = 0;
				sg[0].dma_length = 0;
				break;
			}
		}
		s->dma_address = addr;
		s->dma_length = s->length;
	}
	flush_gart();

	return nents;
}
