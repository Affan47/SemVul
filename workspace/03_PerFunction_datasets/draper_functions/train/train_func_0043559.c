dwc2_handle_session_req_intr(struct dwc2_hsotg *hsotg)
{
	int ret;

	dev_dbg(hsotg->dev, "Session request interrupt - lx_state=%d\n",
							hsotg->lx_state);


	dwc2_writel(GINTSTS_SESSREQINT, hsotg->regs + GINTSTS);

	if (dwc2_is_device_mode(hsotg)) {
		if (hsotg->lx_state == DWC2_L2) {
			ret = dwc2_exit_hibernation(hsotg, true);
			if (ret && (ret != -ENOTSUPP))
				dev_err(hsotg->dev,
					"exit hibernation failed\n");
		}


		dwc2_hsotg_disconnect(hsotg);
	}
}
