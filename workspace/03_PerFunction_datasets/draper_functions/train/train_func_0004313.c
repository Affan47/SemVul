dwc2_hsotg_trytx(struct dwc2_hsotg *hsotg,
			   struct dwc2_hsotg_ep *hs_ep)
{
	struct dwc2_hsotg_req *hs_req = hs_ep->req;

	if (!hs_ep->dir_in || !hs_req) {


		if (hs_ep->index != 0)
			dwc2_hsotg_ctrl_epint(hsotg, hs_ep->index,
					     hs_ep->dir_in, 0);
		return 0;
	}

	if (hs_req->req.actual < hs_req->req.length) {
		dev_dbg(hsotg->dev, "trying to write more for ep%d\n",
			hs_ep->index);
		return dwc2_hsotg_write_fifo(hsotg, hs_ep, hs_req);
	}

	return 0;
}
