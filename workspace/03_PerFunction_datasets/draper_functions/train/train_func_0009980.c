b43_gphy_op_interf_mitigation(struct b43_wldev *dev,
					 enum b43_interference_mitigation mode)
{
	struct b43_phy *phy = &dev->phy;
	struct b43_phy_g *gphy = phy->g;
	int currentmode;

	B43_WARN_ON(phy->type != B43_PHYTYPE_G);
	if ((phy->rev == 0) || (!phy->gmode))
		return -ENODEV;

	gphy->aci_wlan_automatic = false;
	switch (mode) {
	case B43_INTERFMODE_AUTOWLAN:
		gphy->aci_wlan_automatic = true;
		if (gphy->aci_enable)
			mode = B43_INTERFMODE_MANUALWLAN;
		else
			mode = B43_INTERFMODE_NONE;
		break;
	case B43_INTERFMODE_NONE:
	case B43_INTERFMODE_NONWLAN:
	case B43_INTERFMODE_MANUALWLAN:
		break;
	default:
		return -EINVAL;
	}

	currentmode = gphy->interfmode;
	if (currentmode == mode)
		return 0;
	if (currentmode != B43_INTERFMODE_NONE)
		b43_radio_interference_mitigation_disable(dev, currentmode);

	if (mode == B43_INTERFMODE_NONE) {
		gphy->aci_enable = false;
		gphy->aci_hw_rssi = false;
	} else
		b43_radio_interference_mitigation_enable(dev, mode);
	gphy->interfmode = mode;

	return 0;
}
