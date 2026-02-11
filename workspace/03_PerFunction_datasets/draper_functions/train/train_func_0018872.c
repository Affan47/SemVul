c2_mq_free(struct c2_mq *q)
{
	BUG_ON(q->magic != C2_MQ_MAGIC);
	BUG_ON(q->type != C2_MQ_HOST_TARGET);

	if (!c2_mq_empty(q)) {

#ifdef CCMSGMAGIC
		{
			struct c2wr_hdr __iomem *m = (struct c2wr_hdr __iomem *)
			    (q->msg_pool.adapter + q->priv * q->msg_size);
			__raw_writel(cpu_to_be32(~CCWR_MAGIC), &m->magic);
		}
#endif
		q->priv = (q->priv + 1) % q->q_size;

		__raw_writew((__force u16) cpu_to_be16(q->priv), &q->peer->shared);
	}
}
