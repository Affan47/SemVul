dwc3_endpoint_interrupt(struct dwc3 *dwc,
		const struct dwc3_event_depevt *event)
{
	struct dwc3_ep		*dep;
	u8			epnum = event->endpoint_number;

	dep = dwc->eps[epnum];

	if (!(dep->flags & DWC3_EP_ENABLED))
		return;

	if (epnum == 0 || epnum == 1) {
		dwc3_ep0_interrupt(dwc, event);
		return;
	}

	switch (event->endpoint_event) {
	case DWC3_DEPEVT_XFERCOMPLETE:
		dep->resource_index = 0;

		if (usb_endpoint_xfer_isoc(dep->endpoint.desc)) {
			dev_dbg(dwc->dev, "%s is an Isochronous endpoint\n",
					dep->name);
			return;
		}

		dwc3_endpoint_transfer_complete(dwc, dep, event);
		break;
	case DWC3_DEPEVT_XFERINPROGRESS:
		dwc3_endpoint_transfer_complete(dwc, dep, event);
		break;
	case DWC3_DEPEVT_XFERNOTREADY:
		if (usb_endpoint_xfer_isoc(dep->endpoint.desc)) {
			dwc3_gadget_start_isoc(dwc, dep, event);
		} else {
			int active;
			int ret;

			active = event->status & DEPEVT_STATUS_TRANSFER_ACTIVE;

			dwc3_trace(trace_dwc3_gadget, "%s: reason %s",
					dep->name, active ? "Transfer Active"
					: "Transfer Not Active");

			ret = __dwc3_gadget_kick_transfer(dep, 0, !active);
			if (!ret || ret == -EBUSY)
				return;

			dev_dbg(dwc->dev, "%s: failed to kick transfers\n",
					dep->name);
		}

		break;
	case DWC3_DEPEVT_STREAMEVT:
		if (!usb_endpoint_xfer_bulk(dep->endpoint.desc)) {
			dev_err(dwc->dev, "Stream event for non-Bulk %s\n",
					dep->name);
			return;
		}

		switch (event->status) {
		case DEPEVT_STREAMEVT_FOUND:
			dwc3_trace(trace_dwc3_gadget,
					"Stream %d found and started",
					event->parameters);

			break;
		case DEPEVT_STREAMEVT_NOTFOUND:

		default:
			dev_dbg(dwc->dev, "Couldn't find suitable stream\n");
		}
		break;
	case DWC3_DEPEVT_RXTXFIFOEVT:
		dev_dbg(dwc->dev, "%s FIFO Overrun\n", dep->name);
		break;
	case DWC3_DEPEVT_EPCMDCMPLT:
		dwc3_trace(trace_dwc3_gadget, "Endpoint Command Complete");
		break;
	}
}
