dwc3_omap_set_utmi_mode(struct dwc3_omap *omap)
{
	u32			reg;
	struct device_node	*node = omap->dev->of_node;
	int			utmi_mode = 0;

	reg = dwc3_omap_read_utmi_ctrl(omap);

	of_property_read_u32(node, "utmi-mode", &utmi_mode);

	switch (utmi_mode) {
	case DWC3_OMAP_UTMI_MODE_SW:
		reg |= USBOTGSS_UTMI_OTG_CTRL_SW_MODE;
		break;
	case DWC3_OMAP_UTMI_MODE_HW:
		reg &= ~USBOTGSS_UTMI_OTG_CTRL_SW_MODE;
		break;
	default:
		dev_WARN(omap->dev, "UNKNOWN utmi mode %d\n", utmi_mode);
	}

	dwc3_omap_write_utmi_ctrl(omap, reg);
}
