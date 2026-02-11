afs_deliver_fs_store_status(struct afs_call *call,
				       struct sk_buff *skb, bool last)
{
	afs_dataversion_t *store_version;
	struct afs_vnode *vnode = call->reply;
	const __be32 *bp;

	_enter(",,%u", last);

	afs_transfer_reply(call, skb);
	if (!last) {
		_leave(" = 0 [more]");
		return 0;
	}

	if (call->reply_size != call->reply_max) {
		_leave(" = -EBADMSG [%u != %u]",
		       call->reply_size, call->reply_max);
		return -EBADMSG;
	}


	store_version = NULL;
	if (call->operation_ID == FSSTOREDATA)
		store_version = &call->store_version;

	bp = call->buffer;
	xdr_decode_AFSFetchStatus(&bp, &vnode->status, vnode, store_version);


	_leave(" = 0 [done]");
	return 0;
}
