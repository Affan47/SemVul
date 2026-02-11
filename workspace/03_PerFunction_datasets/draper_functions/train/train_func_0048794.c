dwc2_hc_chhltd_intr(struct dwc2_hsotg *hsotg,
				struct dwc2_host_chan *chan, int chnum,
				struct dwc2_qtd *qtd)
{
	if (dbg_hc(chan))
		dev_vdbg(hsotg->dev, "--Host Channel %d Interrupt: Channel Halted--\n",
			 chnum);

	if (hsotg->core_params->dma_enable > 0) {
		dwc2_hc_chhltd_intr_dma(hsotg, chan, chnum, qtd);
	} else {
		if (!dwc2_halt_status_ok(hsotg, chan, chnum, qtd))
			return;
		dwc2_release_channel(hsotg, chan, qtd, chan->halt_status);
	}
}
