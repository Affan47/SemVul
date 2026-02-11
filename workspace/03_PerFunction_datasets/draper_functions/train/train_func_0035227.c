viacam_next_buffer(struct via_camera *cam)
{
	unsigned long flags;
	struct videobuf_buffer *buf = NULL;

	spin_lock_irqsave(&cam->viadev->reg_lock, flags);
	if (cam->opstate != S_RUNNING)
		goto out;
	if (list_empty(&cam->buffer_queue))
		goto out;
	buf = list_entry(cam->buffer_queue.next, struct videobuf_buffer, queue);
	if (!waitqueue_active(&buf->done)) {
		buf = NULL;
		goto out;
	}
	list_del(&buf->queue);
	buf->state = VIDEOBUF_ACTIVE;
out:
	spin_unlock_irqrestore(&cam->viadev->reg_lock, flags);
	return buf;
}
