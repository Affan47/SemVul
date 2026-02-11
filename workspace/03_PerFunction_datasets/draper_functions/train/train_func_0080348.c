ep_set_halt(struct bdc_ep *ep, u32 value)
{
	struct bdc *bdc;
	int ret;

	bdc = ep->bdc;
	dev_dbg(bdc->dev, "%s ep:%s value=%d\n", __func__, ep->name, value);

	if (value) {
		dev_dbg(bdc->dev, "Halt\n");
		if (ep->ep_num == 1)
			bdc->ep0_state = WAIT_FOR_SETUP;

		ret = bdc_ep_set_stall(bdc, ep->ep_num);
		if (ret)
			dev_err(bdc->dev, "failed to set STALL on %s\n",
				ep->name);
		else
			ep->flags |= BDC_EP_STALL;
	} else {

		dev_dbg(bdc->dev, "Before Clear\n");
		ret = bdc_ep_clear_stall(bdc, ep->ep_num);
		if (ret)
			dev_err(bdc->dev, "failed to clear STALL on %s\n",
				ep->name);
		else
			ep->flags &= ~BDC_EP_STALL;
		dev_dbg(bdc->dev, "After  Clear\n");
	}

	return ret;
}
