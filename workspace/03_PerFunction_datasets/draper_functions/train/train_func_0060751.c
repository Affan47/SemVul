dsp_rx_off_member(struct dsp *dsp)
{
	struct mISDN_ctrl_req	cq;
	int rx_off = 1;

	memset(&cq, 0, sizeof(cq));

	if (!dsp->features_rx_off)
		return;


	if (!dsp->rx_disabled)
		rx_off = 0;

	else if (dsp->dtmf.software)
		rx_off = 0;

	else if (dsp->echo.software)
		rx_off = 0;

	else if (dsp->conf && dsp->conf->software)
		rx_off = 0;


	if (rx_off == dsp->rx_is_off)
		return;

	if (!dsp->ch.peer) {
		if (dsp_debug & DEBUG_DSP_CORE)
			printk(KERN_DEBUG "%s: no peer, no rx_off\n",
			       __func__);
		return;
	}
	cq.op = MISDN_CTRL_RX_OFF;
	cq.p1 = rx_off;
	if (dsp->ch.peer->ctrl(dsp->ch.peer, CONTROL_CHANNEL, &cq)) {
		printk(KERN_DEBUG "%s: 2nd CONTROL_CHANNEL failed\n",
		       __func__);
		return;
	}
	dsp->rx_is_off = rx_off;
	if (dsp_debug & DEBUG_DSP_CORE)
		printk(KERN_DEBUG "%s: %s set rx_off = %d\n",
		       __func__, dsp->name, rx_off);
}
