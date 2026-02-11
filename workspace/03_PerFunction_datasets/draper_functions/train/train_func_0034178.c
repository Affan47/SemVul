ia_frontend_intr(struct iadev_priv *iadev)
{
	u32 status;

	if (iadev->phy_type & FE_25MBIT_PHY) {
		status = ia_phy_read32(iadev, MB25_INTR_STATUS);
		iadev->carrier_detect = (status & MB25_IS_GSB) ? 1 : 0;
	} else if (iadev->phy_type & FE_DS3_PHY) {
		ia_phy_read32(iadev, SUNI_DS3_FRM_INTR_STAT);
		status = ia_phy_read32(iadev, SUNI_DS3_FRM_STAT);
		iadev->carrier_detect = (status & SUNI_DS3_LOSV) ? 0 : 1;
	} else if (iadev->phy_type & FE_E3_PHY) {
		ia_phy_read32(iadev, SUNI_E3_FRM_MAINT_INTR_IND);
		status = ia_phy_read32(iadev, SUNI_E3_FRM_FRAM_INTR_IND_STAT);
		iadev->carrier_detect = (status & SUNI_E3_LOS) ? 0 : 1;
	} else {
		status = ia_phy_read32(iadev, SUNI_RSOP_STATUS);
		iadev->carrier_detect = (status & SUNI_LOSV) ? 0 : 1;
	}

	printk(KERN_INFO "IA: SUNI carrier %s\n",
		iadev->carrier_detect ? "detected" : "lost signal");
}
