niu_rx_pkt_ignore(struct niu *np, struct rx_ring_info *rp)
{
	unsigned int index = rp->rcr_index;
	int num_rcr = 0;

	rp->rx_dropped++;
	while (1) {
		struct page *page, **link;
		u64 addr, val;
		u32 rcr_size;

		num_rcr++;

		val = le64_to_cpup(&rp->rcr[index]);
		addr = (val & RCR_ENTRY_PKT_BUF_ADDR) <<
			RCR_ENTRY_PKT_BUF_ADDR_SHIFT;
		page = niu_find_rxpage(rp, addr, &link);

		rcr_size = rp->rbr_sizes[(val & RCR_ENTRY_PKTBUFSZ) >>
					 RCR_ENTRY_PKTBUFSZ_SHIFT];
		if ((page->index + PAGE_SIZE) - rcr_size == addr) {
			*link = (struct page *) page->mapping;
			np->ops->unmap_page(np->device, page->index,
					    PAGE_SIZE, DMA_FROM_DEVICE);
			page->index = 0;
			page->mapping = NULL;
			__free_page(page);
			rp->rbr_refill_pending++;
		}

		index = NEXT_RCR(rp, index);
		if (!(val & RCR_ENTRY_MULTI))
			break;

	}
	rp->rcr_index = index;

	return num_rcr;
}
