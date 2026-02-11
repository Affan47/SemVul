smsc911x_phy_initialise_external(struct smsc911x_data *pdata)
{
	unsigned int hwcfg = smsc911x_reg_read(pdata, HW_CFG);

	if (pdata->config.flags & SMSC911X_FORCE_INTERNAL_PHY) {
		SMSC_TRACE(pdata, hw, "Forcing internal PHY");
		pdata->using_extphy = 0;
	} else if (pdata->config.flags & SMSC911X_FORCE_EXTERNAL_PHY) {
		SMSC_TRACE(pdata, hw, "Forcing external PHY");
		smsc911x_phy_enable_external(pdata);
		pdata->using_extphy = 1;
	} else if (hwcfg & HW_CFG_EXT_PHY_DET_) {
		SMSC_TRACE(pdata, hw,
			   "HW_CFG EXT_PHY_DET set, using external PHY");
		smsc911x_phy_enable_external(pdata);
		pdata->using_extphy = 1;
	} else {
		SMSC_TRACE(pdata, hw,
			   "HW_CFG EXT_PHY_DET clear, using internal PHY");
		pdata->using_extphy = 0;
	}
}
