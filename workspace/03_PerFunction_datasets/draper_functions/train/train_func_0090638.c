usbhs_rcar2_power_ctrl(struct platform_device *pdev,
				void __iomem *base, int enable)
{
	struct usbhs_priv *priv = usbhs_pdev_to_priv(pdev);
	int retval = -ENODEV;

	if (priv->phy) {
		if (enable) {
			retval = phy_init(priv->phy);

			if (!retval)
				retval = phy_power_on(priv->phy);
		} else {
			phy_power_off(priv->phy);
			phy_exit(priv->phy);
			retval = 0;
		}
	}

	if (priv->usb_phy) {
		if (enable) {
			retval = usb_phy_init(priv->usb_phy);

			if (!retval)
				retval = usb_phy_set_suspend(priv->usb_phy, 0);
		} else {
			usb_phy_set_suspend(priv->usb_phy, 1);
			usb_phy_shutdown(priv->usb_phy);
			retval = 0;
		}
	}

	return retval;
}
