mt7601u_usb_submit_buf(struct mt7601u_dev *dev, int dir, int ep_idx,
			   struct mt7601u_dma_buf *buf, gfp_t gfp,
			   usb_complete_t complete_fn, void *context)
{
	struct usb_device *usb_dev = mt7601u_to_usb_dev(dev);
	unsigned pipe;
	int ret;

	if (dir == USB_DIR_IN)
		pipe = usb_rcvbulkpipe(usb_dev, dev->in_eps[ep_idx]);
	else
		pipe = usb_sndbulkpipe(usb_dev, dev->out_eps[ep_idx]);

	usb_fill_bulk_urb(buf->urb, usb_dev, pipe, buf->buf, buf->len,
			  complete_fn, context);
	buf->urb->transfer_dma = buf->dma;
	buf->urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

	trace_mt_submit_urb(dev, buf->urb);
	ret = usb_submit_urb(buf->urb, gfp);
	if (ret)
		dev_err(dev->dev, "Error: submit URB dir:%d ep:%d failed:%d\n",
			dir, ep_idx, ret);
	return ret;
}
