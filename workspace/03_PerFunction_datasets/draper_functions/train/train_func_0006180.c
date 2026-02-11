afs_deliver_cb_probe(struct afs_call *call, struct sk_buff *skb,
				bool last)
{
	_enter(",{%u},%d", skb->len, last);

	if (skb->len > 0)
		return -EBADMSG;
	if (!last)
		return 0;


	call->state = AFS_CALL_REPLYING;

	INIT_WORK(&call->work, SRXAFSCB_Probe);
	queue_work(afs_wq, &call->work);
	return 0;
}
