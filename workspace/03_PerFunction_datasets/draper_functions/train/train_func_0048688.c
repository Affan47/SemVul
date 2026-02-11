__dwc3_gadget_start_isoc(struct dwc3 *dwc,
		struct dwc3_ep *dep, u32 cur_uf)
{
	u32 uf;

	if (list_empty(&dep->request_list)) {
		dwc3_trace(trace_dwc3_gadget,
				"ISOC ep %s run out for requests",
				dep->name);
		dep->flags |= DWC3_EP_PENDING_REQUEST;
		return;
	}


	uf = cur_uf + dep->interval * 4;

	__dwc3_gadget_kick_transfer(dep, uf, 1);
}
