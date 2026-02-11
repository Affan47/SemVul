flatten(env, msg)
	ENV *env;
	struct sending_msg *msg;
{
	u_int8_t *p;
	size_t msg_size;
	int i, ret;

	DB_ASSERT(env, msg->fmsg == NULL);

	msg_size = msg->iovecs->total_bytes;
	if ((ret = __os_malloc(env, sizeof(*msg->fmsg) + msg_size,
	    &msg->fmsg)) != 0)
		return (ret);
	msg->fmsg->length = msg_size;
	msg->fmsg->ref_count = 0;
	p = &msg->fmsg->data[0];

	for (i = 0; i < msg->iovecs->count; i++) {
		memcpy(p, msg->iovecs->vectors[i].iov_base,
		    msg->iovecs->vectors[i].iov_len);
		p = &p[msg->iovecs->vectors[i].iov_len];
	}
	__repmgr_iovec_init(msg->iovecs);
	__repmgr_add_buffer(msg->iovecs, &msg->fmsg->data[0], msg_size);
	return (0);
}
