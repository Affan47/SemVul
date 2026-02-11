afs_collect_incoming_call(struct work_struct *work)
{
	struct rxrpc_call *rxcall;
	struct afs_call *call = NULL;
	struct sk_buff *skb;

	while ((skb = skb_dequeue(&afs_incoming_calls))) {
		_debug("new call");


		afs_free_skb(skb);

		if (!call) {
			call = kzalloc(sizeof(struct afs_call), GFP_KERNEL);
			if (!call) {
				rxrpc_kernel_reject_call(afs_socket);
				return;
			}

			call->async_workfn = afs_process_async_call;
			INIT_WORK(&call->async_work, afs_async_workfn);
			call->wait_mode = &afs_async_incoming_call;
			call->type = &afs_RXCMxxxx;
			init_waitqueue_head(&call->waitq);
			skb_queue_head_init(&call->rx_queue);
			call->state = AFS_CALL_AWAIT_OP_ID;

			_debug("CALL %p{%s} [%d]",
			       call, call->type->name,
			       atomic_read(&afs_outstanding_calls));
			atomic_inc(&afs_outstanding_calls);
		}

		rxcall = rxrpc_kernel_accept_call(afs_socket,
						  (unsigned long) call);
		if (!IS_ERR(rxcall)) {
			call->rxcall = rxcall;
			call = NULL;
		}
	}

	if (call)
		afs_free_call(call);
}
