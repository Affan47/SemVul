gr_set_halt_wedge(struct usb_ep *_ep, int halt, int wedge)
{
	int ret;
	struct gr_ep *ep;

	if (!_ep)
		return -ENODEV;
	ep = container_of(_ep, struct gr_ep, ep);

	spin_lock(&ep->dev->lock);


	if (halt && ep->is_in && !list_empty(&ep->queue)) {
		ret = -EAGAIN;
		goto out;
	}

	ret = gr_ep_halt_wedge(ep, halt, wedge, 0);

out:
	spin_unlock(&ep->dev->lock);

	return ret;
}
