dwc3_omap_set_mailbox(struct dwc3_omap *omap,
	enum omap_dwc3_vbus_id_status status)
{
	int	ret;
	u32	val;

	switch (status) {
	case OMAP_DWC3_ID_GROUND:
		if (omap->vbus_reg) {
			ret = regulator_enable(omap->vbus_reg);
			if (ret) {
				dev_err(omap->dev, "regulator enable failed\n");
				return;
			}
		}

		val = dwc3_omap_read_utmi_ctrl(omap);
		val &= ~(USBOTGSS_UTMI_OTG_CTRL_IDDIG
				| USBOTGSS_UTMI_OTG_CTRL_VBUSVALID
				| USBOTGSS_UTMI_OTG_CTRL_SESSEND);
		val |= USBOTGSS_UTMI_OTG_CTRL_SESSVALID
				| USBOTGSS_UTMI_OTG_CTRL_POWERPRESENT;
		dwc3_omap_write_utmi_ctrl(omap, val);
		break;

	case OMAP_DWC3_VBUS_VALID:
		val = dwc3_omap_read_utmi_ctrl(omap);
		val &= ~USBOTGSS_UTMI_OTG_CTRL_SESSEND;
		val |= USBOTGSS_UTMI_OTG_CTRL_IDDIG
				| USBOTGSS_UTMI_OTG_CTRL_VBUSVALID
				| USBOTGSS_UTMI_OTG_CTRL_SESSVALID
				| USBOTGSS_UTMI_OTG_CTRL_POWERPRESENT;
		dwc3_omap_write_utmi_ctrl(omap, val);
		break;

	case OMAP_DWC3_ID_FLOAT:
		if (omap->vbus_reg)
			regulator_disable(omap->vbus_reg);

	case OMAP_DWC3_VBUS_OFF:
		val = dwc3_omap_read_utmi_ctrl(omap);
		val &= ~(USBOTGSS_UTMI_OTG_CTRL_SESSVALID
				| USBOTGSS_UTMI_OTG_CTRL_VBUSVALID
				| USBOTGSS_UTMI_OTG_CTRL_POWERPRESENT);
		val |= USBOTGSS_UTMI_OTG_CTRL_SESSEND
				| USBOTGSS_UTMI_OTG_CTRL_IDDIG;
		dwc3_omap_write_utmi_ctrl(omap, val);
		break;

	default:
		dev_WARN(omap->dev, "invalid state\n");
	}
}
