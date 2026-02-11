cobalt_buf_queue(struct vb2_buffer *vb)
{
	struct vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	struct vb2_queue *q = vb->vb2_queue;
	struct cobalt_stream *s = q->drv_priv;
	struct cobalt_buffer *cb = to_cobalt_buffer(vbuf);
	struct sg_dma_desc_info *desc = &s->dma_desc_info[vb->index];
	unsigned long flags;


	descriptor_list_loopback(desc);
	descriptor_list_interrupt_disable(desc);

	spin_lock_irqsave(&s->irqlock, flags);
	list_add_tail(&cb->list, &s->bufs);
	chain_all_buffers(s);
	spin_unlock_irqrestore(&s->irqlock, flags);
}
