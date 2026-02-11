xpc_received_payload_uv(struct xpc_channel *ch, void *payload)
{
	struct xpc_notify_mq_msg_uv *msg;
	enum xp_retval ret;

	msg = container_of(payload, struct xpc_notify_mq_msg_uv, payload);


	msg->hdr.partid = xp_partition_id;
	msg->hdr.size = 0;

	ret = xpc_send_gru_msg(ch->sn.uv.cached_notify_gru_mq_desc, msg,
			       sizeof(struct xpc_notify_mq_msghdr_uv));
	if (ret != xpSuccess)
		XPC_DEACTIVATE_PARTITION(&xpc_partitions[ch->partid], ret);
}
