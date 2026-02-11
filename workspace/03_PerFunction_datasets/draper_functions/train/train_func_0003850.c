c2_mq_req_init(struct c2_mq *q, u32 index, u32 q_size, u32 msg_size,
		    u8 __iomem *pool_start, u16 __iomem *peer, u32 type)
{
	BUG_ON(!q->shared);


	q->index = index;
	q->q_size = q_size;
	q->msg_size = msg_size;
	q->msg_pool.adapter = pool_start;
	q->peer = (struct c2_mq_shared __iomem *) peer;
	q->magic = C2_MQ_MAGIC;
	q->type = type;
	q->priv = 0;
	q->hint_count = 0;
	return;
}
