dwc3_prepare_one_trb(struct dwc3_ep *dep,
		struct dwc3_request *req, dma_addr_t dma,
		unsigned length, unsigned last, unsigned chain, unsigned node)
{
	struct dwc3_trb		*trb;

	dwc3_trace(trace_dwc3_gadget, "%s: req %p dma %08llx length %d%s%s",
			dep->name, req, (unsigned long long) dma,
			length, last ? " last" : "",
			chain ? " chain" : "");


	trb = &dep->trb_pool[dep->free_slot & DWC3_TRB_MASK];

	if (!req->trb) {
		dwc3_gadget_move_request_queued(req);
		req->trb = trb;
		req->trb_dma = dwc3_trb_dma_offset(dep, trb);
		req->start_slot = dep->free_slot & DWC3_TRB_MASK;
	}

	dep->free_slot++;

	if (((dep->free_slot & DWC3_TRB_MASK) == DWC3_TRB_NUM - 1) &&
			usb_endpoint_xfer_isoc(dep->endpoint.desc))
		dep->free_slot++;

	trb->size = DWC3_TRB_SIZE_LENGTH(length);
	trb->bpl = lower_32_bits(dma);
	trb->bph = upper_32_bits(dma);

	switch (usb_endpoint_type(dep->endpoint.desc)) {
	case USB_ENDPOINT_XFER_CONTROL:
		trb->ctrl = DWC3_TRBCTL_CONTROL_SETUP;
		break;

	case USB_ENDPOINT_XFER_ISOC:
		if (!node)
			trb->ctrl = DWC3_TRBCTL_ISOCHRONOUS_FIRST;
		else
			trb->ctrl = DWC3_TRBCTL_ISOCHRONOUS;
		break;

	case USB_ENDPOINT_XFER_BULK:
	case USB_ENDPOINT_XFER_INT:
		trb->ctrl = DWC3_TRBCTL_NORMAL;
		break;
	default:


		BUG();
	}

	if (!req->request.no_interrupt && !chain)
		trb->ctrl |= DWC3_TRB_CTRL_IOC;

	if (usb_endpoint_xfer_isoc(dep->endpoint.desc)) {
		trb->ctrl |= DWC3_TRB_CTRL_ISP_IMI;
		trb->ctrl |= DWC3_TRB_CTRL_CSP;
	} else if (last) {
		trb->ctrl |= DWC3_TRB_CTRL_LST;
	}

	if (chain)
		trb->ctrl |= DWC3_TRB_CTRL_CHN;

	if (usb_endpoint_xfer_bulk(dep->endpoint.desc) && dep->stream_capable)
		trb->ctrl |= DWC3_TRB_CTRL_SID_SOFN(req->request.stream_id);

	trb->ctrl |= DWC3_TRB_CTRL_HWO;

	trace_dwc3_prepare_trb(dep, trb);
}
