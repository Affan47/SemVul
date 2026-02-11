tce_build(struct iommu_table *tbl, unsigned long index,
	unsigned int npages, unsigned long uaddr, int direction)
{
	u64* tp;
	u64 t;
	u64 rpn;

	t = (1 << TCE_READ_SHIFT);
	if (direction != DMA_TO_DEVICE)
		t |= (1 << TCE_WRITE_SHIFT);

	tp = ((u64*)tbl->it_base) + index;

	while (npages--) {
		rpn = (virt_to_bus((void*)uaddr)) >> PAGE_SHIFT;
		t &= ~TCE_RPN_MASK;
		t |= (rpn << TCE_RPN_SHIFT);

		*tp = cpu_to_be64(t);
		flush_tce(tp);

		uaddr += PAGE_SIZE;
		tp++;
	}
}
