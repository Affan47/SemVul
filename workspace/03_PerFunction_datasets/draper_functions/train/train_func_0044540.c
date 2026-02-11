sst_hsw_stream_new(struct sst_hsw *hsw, int id,
	u32 (*notify_position)(struct sst_hsw_stream *stream, void *data),
	void *data)
{
	struct sst_hsw_stream *stream;
	struct sst_dsp *sst = hsw->dsp;
	unsigned long flags;

	stream = kzalloc(sizeof(*stream), GFP_KERNEL);
	if (stream == NULL)
		return NULL;

	spin_lock_irqsave(&sst->spinlock, flags);
	stream->reply.stream_hw_id = INVALID_STREAM_HW_ID;
	list_add(&stream->node, &hsw->stream_list);
	stream->notify_position = notify_position;
	stream->pdata = data;
	stream->hsw = hsw;
	stream->host_id = id;


	INIT_WORK(&stream->notify_work, hsw_notification_work);
	spin_unlock_irqrestore(&sst->spinlock, flags);

	return stream;
}
