__repmgr_defer_op(env, op)
	ENV *env;
	u_int32_t op;
{
	REPMGR_MESSAGE *msg;
	int ret;


	if ((ret = __os_calloc(env, 1, sizeof(*msg), &msg)) != 0)
		return (ret);
	msg->msg_hdr.type = REPMGR_OWN_MSG;
	REPMGR_OWN_MSG_TYPE(msg->msg_hdr) = op;
	ret = __repmgr_queue_put(env, msg);
	return (ret);
}
