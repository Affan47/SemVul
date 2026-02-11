buffer_queue(struct vb2_buffer *vb)
{
	struct vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	struct cx8800_dev *dev = vb->vb2_queue->drv_priv;
	struct cx88_buffer    *buf = container_of(vbuf, struct cx88_buffer, vb);
	struct cx88_buffer    *prev;
	struct cx88_core      *core = dev->core;
	struct cx88_dmaqueue  *q    = &dev->vidq;


	buf->risc.cpu[1] = cpu_to_le32(buf->risc.dma + 8);
	buf->risc.jmp[0] = cpu_to_le32(RISC_JUMP | RISC_CNT_INC);
	buf->risc.jmp[1] = cpu_to_le32(buf->risc.dma + 8);

	if (list_empty(&q->active)) {
		list_add_tail(&buf->list, &q->active);
		dprintk(2,"[%p/%d] buffer_queue - first active\n",
			buf, buf->vb.vb2_buf.index);

	} else {
		buf->risc.cpu[0] |= cpu_to_le32(RISC_IRQ1);
		prev = list_entry(q->active.prev, struct cx88_buffer, list);
		list_add_tail(&buf->list, &q->active);
		prev->risc.jmp[1] = cpu_to_le32(buf->risc.dma);
		dprintk(2, "[%p/%d] buffer_queue - append to active\n",
			buf, buf->vb.vb2_buf.index);
	}
}
