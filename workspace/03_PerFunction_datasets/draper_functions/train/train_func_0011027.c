read_radio_reg(struct brcms_phy *pi, u16 addr)
{
	u16 data;

	if ((addr == RADIO_IDCODE))
		return 0xffff;

	switch (pi->pubpi.phy_type) {
	case PHY_TYPE_N:
		if (!CONF_HAS(PHYTYPE, PHY_TYPE_N))
			break;
		if (NREV_GE(pi->pubpi.phy_rev, 7))
			addr |= RADIO_2057_READ_OFF;
		else
			addr |= RADIO_2055_READ_OFF;
		break;

	case PHY_TYPE_LCN:
		if (!CONF_HAS(PHYTYPE, PHY_TYPE_LCN))
			break;
		addr |= RADIO_2064_READ_OFF;
		break;

	default:
		break;
	}

	if ((D11REV_GE(pi->sh->corerev, 24)) ||
	    (D11REV_IS(pi->sh->corerev, 22)
	     && (pi->pubpi.phy_type != PHY_TYPE_SSN))) {
		bcma_wflush16(pi->d11core, D11REGOFFS(radioregaddr), addr);
		data = bcma_read16(pi->d11core, D11REGOFFS(radioregdata));
	} else {
		bcma_wflush16(pi->d11core, D11REGOFFS(phy4waddr), addr);
		data = bcma_read16(pi->d11core, D11REGOFFS(phy4wdatalo));
	}
	pi->phy_wreg = 0;

	return data;
}
