mv_u3d_ep_set_halt_wedge(struct usb_ep *_ep, int halt, int wedge)
{
	struct mv_u3d_ep *ep;
	unsigned long flags = 0;
	int status = 0;
	struct mv_u3d *u3d;

	ep = container_of(_ep, struct mv_u3d_ep, ep);
	u3d = ep->u3d;
	if (!ep->ep.desc) {
		status = -EINVAL;
		goto out;
	}

	if (ep->ep.desc->bmAttributes == USB_ENDPOINT_XFER_ISOC) {
		status = -EOPNOTSUPP;
		goto out;
	}


	if (halt && (mv_u3d_ep_dir(ep) == MV_U3D_EP_DIR_IN)
			&& !list_empty(&ep->queue)) {
		status = -EAGAIN;
		goto out;
	}

	spin_lock_irqsave(&ep->u3d->lock, flags);
	mv_u3d_ep_set_stall(u3d, ep->ep_num, mv_u3d_ep_dir(ep), halt);
	if (halt && wedge)
		ep->wedge = 1;
	else if (!halt)
		ep->wedge = 0;
	spin_unlock_irqrestore(&ep->u3d->lock, flags);

	if (ep->ep_num == 0)
		u3d->ep0_dir = MV_U3D_EP_DIR_OUT;
out:
	return status;
}
