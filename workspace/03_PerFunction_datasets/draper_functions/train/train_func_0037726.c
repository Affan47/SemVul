prepare_transfer(struct xhci_hcd *xhci,
		struct xhci_virt_device *xdev,
		unsigned int ep_index,
		unsigned int stream_id,
		unsigned int num_trbs,
		struct urb *urb,
		unsigned int td_index,
		gfp_t mem_flags)
{
	int ret;
	struct urb_priv *urb_priv;
	struct xhci_td	*td;
	struct xhci_ring *ep_ring;
	struct xhci_ep_ctx *ep_ctx = xhci_get_ep_ctx(xhci, xdev->out_ctx, ep_index);

	ep_ring = xhci_stream_id_to_ring(xdev, ep_index, stream_id);
	if (!ep_ring) {
		xhci_dbg(xhci, "Can't prepare ring for bad stream ID %u\n",
				stream_id);
		return -EINVAL;
	}

	ret = prepare_ring(xhci, ep_ring,
			   le32_to_cpu(ep_ctx->ep_info) & EP_STATE_MASK,
			   num_trbs, mem_flags);
	if (ret)
		return ret;

	urb_priv = urb->hcpriv;
	td = urb_priv->td[td_index];

	INIT_LIST_HEAD(&td->td_list);
	INIT_LIST_HEAD(&td->cancelled_td_list);

	if (td_index == 0) {
		ret = usb_hcd_link_urb_to_ep(bus_to_hcd(urb->dev->bus), urb);
		if (unlikely(ret))
			return ret;
	}

	td->urb = urb;

	list_add_tail(&td->td_list, &ep_ring->td_list);
	td->start_seg = ep_ring->enq_seg;
	td->first_trb = ep_ring->enqueue;

	urb_priv->td[td_index] = td;

	return 0;
}
