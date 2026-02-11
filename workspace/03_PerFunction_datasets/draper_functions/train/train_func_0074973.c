mq_tcp_flushed(const mqueue_t *q)
{
	pmsg_t *mb;

	if (NULL == q->qtail)
		return TRUE;

	mb = q->qtail->data;
	return pmsg_is_unread(mb);
}
