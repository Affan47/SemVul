au0828_vbi_buffer_timeout(unsigned long data)
{
	struct au0828_dev *dev = (struct au0828_dev *) data;
	struct au0828_dmaqueue *dma_q = &dev->vbiq;
	struct au0828_buffer *buf;
	unsigned char *vbi_data;
	unsigned long flags = 0;

	spin_lock_irqsave(&dev->slock, flags);

	buf = dev->isoc_ctl.vbi_buf;
	if (buf != NULL) {
		vbi_data = vb2_plane_vaddr(&buf->vb.vb2_buf, 0);
		memset(vbi_data, 0x00, buf->length);
		buffer_filled(dev, dma_q, buf);
	}
	vbi_get_next_buf(dma_q, &buf);

	if (dev->vbi_timeout_running == 1)
		mod_timer(&dev->vbi_timeout, jiffies + (HZ / 10));
	spin_unlock_irqrestore(&dev->slock, flags);
}
