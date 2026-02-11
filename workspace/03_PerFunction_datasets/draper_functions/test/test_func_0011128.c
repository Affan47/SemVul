release_ptd_buffers(struct isp1362_ep_queue *epq, struct isp1362_ep *ep)
{
	int last = ep->ptd_index + ep->num_ptds;

	if (last > epq->buf_count)
		pr_err("%s: ep %p req %d len %d %s PTD[%d] $%04x num_ptds %d buf_count %d buf_avail %d buf_map %08lx skip_map %08lx\n",
		    __func__, ep, ep->num_req, ep->length, epq->name, ep->ptd_index,
		    ep->ptd_offset, ep->num_ptds, epq->buf_count, epq->buf_avail,
		    epq->buf_map, epq->skip_map);
	BUG_ON(last > epq->buf_count);

	bitmap_clear(&epq->buf_map, ep->ptd_index, ep->num_ptds);
	bitmap_set(&epq->skip_map, ep->ptd_index, ep->num_ptds);
	epq->buf_avail += ep->num_ptds;
	epq->ptd_count--;

	BUG_ON(epq->buf_avail > epq->buf_count);
	BUG_ON(epq->ptd_count > epq->buf_count);

	DBG(1, "%s: Done %s PTDs $%04x released %d avail %d count %d\n",
	    __func__, epq->name,
	    ep->ptd_offset, ep->num_ptds, epq->buf_avail, epq->buf_count);
	DBG(1, "%s: buf_map %08lx skip_map %08lx\n", __func__,
	    epq->buf_map, epq->skip_map);

	ep->num_ptds = 0;
	ep->ptd_offset = -EINVAL;
	ep->ptd_index = -EINVAL;
}
