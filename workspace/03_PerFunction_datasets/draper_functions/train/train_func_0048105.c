enqueue_reorder_recvframe(struct recv_reorder_ctrl *preorder_ctrl,
			      union recv_frame *prframe)
{
	struct list_head *phead, *plist;
	union recv_frame *pnextrframe;
	struct rx_pkt_attrib *pnextattrib;
	struct  __queue *ppending_recvframe_queue =
					&preorder_ctrl->pending_recvframe_queue;
	struct rx_pkt_attrib *pattrib = &prframe->u.hdr.attrib;

	phead = &ppending_recvframe_queue->queue;
	plist = phead->next;
	while (!end_of_queue_search(phead, plist)) {
		pnextrframe = LIST_CONTAINOR(plist, union recv_frame, u);
		pnextattrib = &pnextrframe->u.hdr.attrib;
		if (SN_LESS(pnextattrib->seq_num, pattrib->seq_num))
			plist = plist->next;
		else if (SN_EQUAL(pnextattrib->seq_num, pattrib->seq_num))
			return false;
		else
			break;
	}
	list_del_init(&(prframe->u.hdr.list));
	list_add_tail(&(prframe->u.hdr.list), plist);
	return true;
}
