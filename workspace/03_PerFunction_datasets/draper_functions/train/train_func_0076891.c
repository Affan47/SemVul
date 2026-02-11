xpc_send_activate_IRQ_part_uv(struct xpc_partition *part, void *msg,
			      size_t msg_size, int msg_type)
{
	enum xp_retval ret;

	ret = xpc_send_activate_IRQ_uv(part, msg, msg_size, msg_type);
	if (unlikely(ret != xpSuccess))
		XPC_DEACTIVATE_PARTITION(part, ret);
}
