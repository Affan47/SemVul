mcam_vb_requeue_bufs(struct vb2_queue *vq,
				 enum vb2_buffer_state state)
{
	struct mcam_camera *cam = vb2_get_drv_priv(vq);
	struct mcam_vb_buffer *buf, *node;
	unsigned long flags;
	unsigned i;

	spin_lock_irqsave(&cam->dev_lock, flags);
	list_for_each_entry_safe(buf, node, &cam->buffers, queue) {
		vb2_buffer_done(&buf->vb_buf.vb2_buf, state);
		list_del(&buf->queue);
	}
	for (i = 0; i < MAX_DMA_BUFS; i++) {
		buf = cam->vb_bufs[i];

		if (buf) {
			vb2_buffer_done(&buf->vb_buf.vb2_buf, state);
			cam->vb_bufs[i] = NULL;
		}
	}
	spin_unlock_irqrestore(&cam->dev_lock, flags);
}
