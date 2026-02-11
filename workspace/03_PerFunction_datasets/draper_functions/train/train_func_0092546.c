dwc2_hsotg_ep_queue(struct usb_ep *ep, struct usb_request *req,
			      gfp_t gfp_flags)
{
	struct dwc2_hsotg_req *hs_req = our_req(req);
	struct dwc2_hsotg_ep *hs_ep = our_ep(ep);
	struct dwc2_hsotg *hs = hs_ep->parent;
	bool first;
	int ret;

	dev_dbg(hs->dev, "%s: req %p: %d@%p, noi=%d, zero=%d, snok=%d\n",
		ep->name, req, req->length, req->buf, req->no_interrupt,
		req->zero, req->short_not_ok);


	if (hs->lx_state == DWC2_L2) {
		dev_dbg(hs->dev, "%s: don't submit request while suspended\n",
				__func__);
		return -EAGAIN;
	}


	INIT_LIST_HEAD(&hs_req->queue);
	req->actual = 0;
	req->status = -EINPROGRESS;

	ret = dwc2_hsotg_handle_unaligned_buf_start(hs, hs_ep, hs_req);
	if (ret)
		return ret;


	if (using_dma(hs)) {
		ret = dwc2_hsotg_map_dma(hs, hs_ep, req);
		if (ret)
			return ret;
	}

	first = list_empty(&hs_ep->queue);
	list_add_tail(&hs_req->queue, &hs_ep->queue);

	if (first)
		dwc2_hsotg_start_req(hs, hs_ep, hs_req, false);

	return 0;
}
