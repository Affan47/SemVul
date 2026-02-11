get_next_buf(struct au0828_dmaqueue *dma_q,
				struct au0828_buffer **buf)
{
	struct au0828_dev *dev = container_of(dma_q, struct au0828_dev, vidq);

	if (list_empty(&dma_q->active)) {
		au0828_isocdbg("No active queue to serve\n");
		dev->isoc_ctl.buf = NULL;
		*buf = NULL;
		return;
	}


	*buf = list_entry(dma_q->active.next, struct au0828_buffer, list);

	list_del(&(*buf)->list);
	dma_q->pos = 0;
	(*buf)->vb_buf = (*buf)->mem;
	dev->isoc_ctl.buf = *buf;

	return;
}
