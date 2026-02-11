brcms_c_isgoodchip(struct brcms_hardware *wlc_hw)
{


	if (!CONF_HAS(D11CONF, wlc_hw->corerev)) {
		wiphy_err(wlc_hw->wlc->wiphy, "unsupported core rev %d\n",
			  wlc_hw->corerev);
		return false;
	}

	return true;
}
