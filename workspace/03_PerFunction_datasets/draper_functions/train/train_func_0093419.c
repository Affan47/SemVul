goku_queue(struct usb_ep *_ep, struct usb_request *_req, gfp_t gfp_flags)
{
	struct goku_request	*req;
	struct goku_ep		*ep;
	struct goku_udc		*dev;
	unsigned long		flags;
	int			status;


	req = container_of(_req, struct goku_request, req);
	if (unlikely(!_req || !_req->complete
			|| !_req->buf || !list_empty(&req->queue)))
		return -EINVAL;
	ep = container_of(_ep, struct goku_ep, ep);
	if (unlikely(!_ep || (!ep->ep.desc && ep->num != 0)))
		return -EINVAL;
	dev = ep->dev;
	if (unlikely(!dev->driver || dev->gadget.speed == USB_SPEED_UNKNOWN))
		return -ESHUTDOWN;


	if (dev->ep0state == EP0_SUSPEND)
		return -EBUSY;


	if (ep->dma) {
		status = usb_gadget_map_request(&dev->gadget, &req->req,
				ep->is_in);
		if (status)
			return status;
	}

#ifdef USB_TRACE
	VDBG(dev, "%s queue req %p, len %u buf %p\n",
			_ep->name, _req, _req->length, _req->buf);
#endif

	spin_lock_irqsave(&dev->lock, flags);

	_req->status = -EINPROGRESS;
	_req->actual = 0;


	if (unlikely(ep->num == 0 && ep->is_in))
		_req->zero = 1;


	status = 0;
	if (list_empty(&ep->queue) && likely(!ep->stopped)) {


		if (ep->dma)
			status = start_dma(ep, req);
		else
			status = (ep->is_in ? write_fifo : read_fifo)(ep, req);

		if (unlikely(status != 0)) {
			if (status > 0)
				status = 0;
			req = NULL;
		}

	}

	if (likely(req != NULL))
		list_add_tail(&req->queue, &ep->queue);

	if (likely(!list_empty(&ep->queue))
			&& likely(ep->num != 0)
			&& !ep->dma
			&& !(dev->int_enable & INT_EPxDATASET (ep->num)))
		pio_irq_enable(dev, dev->regs, ep->num);

	spin_unlock_irqrestore(&dev->lock, flags);


	return status;
}
