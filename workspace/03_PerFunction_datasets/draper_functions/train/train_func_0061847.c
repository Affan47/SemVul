get_next_seg(struct list_head *rmpp_list,
						    struct ib_mad_recv_buf *seg)
{
	if (seg->list.next == rmpp_list)
		return NULL;

	return container_of(seg->list.next, struct ib_mad_recv_buf, list);
}
