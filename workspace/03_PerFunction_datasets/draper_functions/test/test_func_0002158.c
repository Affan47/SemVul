_brcms_c_stf_phytxchain_sel(struct brcms_c_info *wlc,
				       u32 rspec)
{
	u16 phytxant = wlc->stf->phytxant;

	if (rspec_stf(rspec) != PHY_TXC1_MODE_SISO)
		phytxant = wlc->stf->txchain << PHY_TXC_ANT_SHIFT;
	else if (wlc->stf->txant == ANT_TX_DEF)
		phytxant = wlc->stf->txchain << PHY_TXC_ANT_SHIFT;
	phytxant &= PHY_TXC_ANT_MASK;
	return phytxant;
}
