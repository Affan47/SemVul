isp1760_udc_irq(int irq, void *dev)
{
	struct isp1760_udc *udc = dev;
	unsigned int i;
	u32 status;

	status = isp1760_udc_read(udc, DC_INTERRUPT)
	       & isp1760_udc_read(udc, DC_INTENABLE);
	isp1760_udc_write(udc, DC_INTERRUPT, status);

	if (status & DC_IEVBUS) {
		dev_dbg(udc->isp->dev, "%s(VBUS)\n", __func__);

		spin_lock(&udc->lock);
		isp1760_udc_connect(udc);
		spin_unlock(&udc->lock);
	}

	if (status & DC_IEBRST) {
		dev_dbg(udc->isp->dev, "%s(BRST)\n", __func__);

		isp1760_udc_reset(udc);
	}

	for (i = 0; i <= 7; ++i) {
		struct isp1760_ep *ep = &udc->ep[i*2];

		if (status & DC_IEPTX(i)) {
			dev_dbg(udc->isp->dev, "%s(EPTX%u)\n", __func__, i);
			isp1760_ep_tx_complete(ep);
		}

		if (status & DC_IEPRX(i)) {
			dev_dbg(udc->isp->dev, "%s(EPRX%u)\n", __func__, i);
			isp1760_ep_rx_ready(i ? ep - 1 : ep);
		}
	}

	if (status & DC_IEP0SETUP) {
		dev_dbg(udc->isp->dev, "%s(EP0SETUP)\n", __func__);

		isp1760_ep0_setup(udc);
	}

	if (status & DC_IERESM) {
		dev_dbg(udc->isp->dev, "%s(RESM)\n", __func__);
		isp1760_udc_resume(udc);
	}

	if (status & DC_IESUSP) {
		dev_dbg(udc->isp->dev, "%s(SUSP)\n", __func__);

		spin_lock(&udc->lock);
		if (!(isp1760_udc_read(udc, DC_MODE) & DC_VBUSSTAT))
			isp1760_udc_disconnect(udc);
		else
			isp1760_udc_suspend(udc);
		spin_unlock(&udc->lock);
	}

	if (status & DC_IEHS_STA) {
		dev_dbg(udc->isp->dev, "%s(HS_STA)\n", __func__);
		udc->gadget.speed = USB_SPEED_HIGH;
	}

	return status ? IRQ_HANDLED : IRQ_NONE;
}
