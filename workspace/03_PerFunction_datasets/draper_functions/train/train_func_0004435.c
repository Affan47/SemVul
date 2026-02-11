pch_udc_wait_ep_stall(struct pch_udc_ep *ep)
{
	unsigned int count = 10000;


	while ((pch_udc_read_ep_control(ep) & UDC_EPCTL_S) && --count)
		udelay(5);
	if (!count)
		dev_err(&ep->dev->pdev->dev, "%s: wait error\n", __func__);
}
