nxp_nci_i2c_set_mode(void *phy_id,
				    enum nxp_nci_mode mode)
{
	struct nxp_nci_i2c_phy *phy = (struct nxp_nci_i2c_phy *) phy_id;

	gpio_set_value(phy->gpio_fw, (mode == NXP_NCI_MODE_FW) ? 1 : 0);
	gpio_set_value(phy->gpio_en, (mode != NXP_NCI_MODE_COLD) ? 1 : 0);
	usleep_range(10000, 15000);

	if (mode == NXP_NCI_MODE_COLD)
		phy->hard_fault = 0;

	return 0;
}
