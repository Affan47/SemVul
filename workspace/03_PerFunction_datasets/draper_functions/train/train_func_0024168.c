videobuf_queue_core_init(struct videobuf_queue *q,
			 const struct videobuf_queue_ops *ops,
			 struct device *dev,
			 spinlock_t *irqlock,
			 enum v4l2_buf_type type,
			 enum v4l2_field field,
			 unsigned int msize,
			 void *priv,
			 struct videobuf_qtype_ops *int_ops,
			 struct mutex *ext_lock)
{
	BUG_ON(!q);
	memset(q, 0, sizeof(*q));
	q->irqlock   = irqlock;
	q->ext_lock  = ext_lock;
	q->dev       = dev;
	q->type      = type;
	q->field     = field;
	q->msize     = msize;
	q->ops       = ops;
	q->priv_data = priv;
	q->int_ops   = int_ops;


	BUG_ON(!q->ops->buf_setup);
	BUG_ON(!q->ops->buf_prepare);
	BUG_ON(!q->ops->buf_queue);
	BUG_ON(!q->ops->buf_release);


	BUG_ON(!irqlock);


	BUG_ON(!q->int_ops);

	mutex_init(&q->vb_lock);
	init_waitqueue_head(&q->wait);
	INIT_LIST_HEAD(&q->stream);
}
