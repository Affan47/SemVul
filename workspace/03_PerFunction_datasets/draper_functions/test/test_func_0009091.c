afs_deliver_cb_init_call_back_state(struct afs_call *call,
					       struct sk_buff *skb,
					       bool last)
{
	struct afs_server *server;
	struct in_addr addr;

	_enter(",{%u},%d", skb->len, last);

	if (skb->len > 0)
		return -EBADMSG;
	if (!last)
		return 0;


	call->state = AFS_CALL_REPLYING;


	memcpy(&addr, &ip_hdr(skb)->saddr, 4);
	server = afs_find_server(&addr);
	if (!server)
		return -ENOTCONN;
	call->server = server;

	INIT_WORK(&call->work, SRXAFSCB_InitCallBackState);
	queue_work(afs_wq, &call->work);
	return 0;
}
