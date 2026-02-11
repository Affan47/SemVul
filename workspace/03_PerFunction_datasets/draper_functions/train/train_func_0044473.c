dwc2_halt_channel(struct dwc2_hsotg *hsotg,
			      struct dwc2_host_chan *chan, struct dwc2_qtd *qtd,
			      enum dwc2_halt_status halt_status)
{
	if (dbg_hc(chan))
		dev_vdbg(hsotg->dev, "%s()\n", __func__);

	if (hsotg->core_params->dma_enable > 0) {
		if (dbg_hc(chan))
			dev_vdbg(hsotg->dev, "DMA enabled\n");
		dwc2_release_channel(hsotg, chan, qtd, halt_status);
		return;
	}


	dwc2_hc_halt(hsotg, chan, halt_status);

	if (chan->halt_on_queue) {
		u32 gintmsk;

		dev_vdbg(hsotg->dev, "Halt on queue\n");
		if (chan->ep_type == USB_ENDPOINT_XFER_CONTROL ||
		    chan->ep_type == USB_ENDPOINT_XFER_BULK) {
			dev_vdbg(hsotg->dev, "control/bulk\n");


			gintmsk = dwc2_readl(hsotg->regs + GINTMSK);
			gintmsk |= GINTSTS_NPTXFEMP;
			dwc2_writel(gintmsk, hsotg->regs + GINTMSK);
		} else {
			dev_vdbg(hsotg->dev, "isoc/intr\n");


			list_move(&chan->qh->qh_list_entry,
				  &hsotg->periodic_sched_assigned);


			gintmsk = dwc2_readl(hsotg->regs + GINTMSK);
			gintmsk |= GINTSTS_PTXFEMP;
			dwc2_writel(gintmsk, hsotg->regs + GINTMSK);
		}
	}
}
