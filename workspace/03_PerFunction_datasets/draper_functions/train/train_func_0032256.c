nicvf_alloc_rcv_buffer(struct nicvf *nic, gfp_t gfp,
					 u32 buf_len, u64 **rbuf)
{
	int order = (PAGE_SIZE <= 4096) ?  PAGE_ALLOC_COSTLY_ORDER : 0;


	if (nic->rb_page &&
	    ((nic->rb_page_offset + buf_len) < (PAGE_SIZE << order))) {
		nic->rb_pageref++;
		goto ret;
	}

	nicvf_get_page(nic);
	nic->rb_page = NULL;


	if (!nic->rb_page) {
		nic->rb_page = alloc_pages(gfp | __GFP_COMP | __GFP_NOWARN,
					   order);
		if (!nic->rb_page) {
			nic->drv_stats.rcv_buffer_alloc_failures++;
			return -ENOMEM;
		}
		nic->rb_page_offset = 0;
	}

ret:
	*rbuf = (u64 *)((u64)page_address(nic->rb_page) + nic->rb_page_offset);
	nic->rb_page_offset += buf_len;

	return 0;
}
