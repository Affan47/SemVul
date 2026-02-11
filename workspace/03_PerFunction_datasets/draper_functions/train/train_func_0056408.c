rtw_free_recvframe23a_queue(struct rtw_queue *pframequeue)
{
	struct recv_frame *hdr;
	struct list_head *plist, *phead, *ptmp;

	spin_lock(&pframequeue->lock);

	phead = get_list_head(pframequeue);
	plist = phead->next;

	list_for_each_safe(plist, ptmp, phead) {
		hdr = container_of(plist, struct recv_frame, list);
		rtw_free_recvframe23a(hdr);
	}

	spin_unlock(&pframequeue->lock);
}
