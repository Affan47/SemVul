wusbhc_rh_clear_port_feat(struct wusbhc *wusbhc, u16 feature,
				     u8 selector, u8 port_idx)
{
	int result = 0;
	struct device *dev = wusbhc->dev;

	if (port_idx > wusbhc->ports_max)
		return -EINVAL;

	mutex_lock(&wusbhc->mutex);
	switch (feature) {
	case USB_PORT_FEAT_POWER:

	case USB_PORT_FEAT_C_OVER_CURRENT:
		break;
	case USB_PORT_FEAT_C_RESET:
		wusb_port_by_idx(wusbhc, port_idx)->change &= ~USB_PORT_STAT_C_RESET;
		break;
	case USB_PORT_FEAT_C_CONNECTION:
		wusb_port_by_idx(wusbhc, port_idx)->change &= ~USB_PORT_STAT_C_CONNECTION;
		break;
	case USB_PORT_FEAT_ENABLE:
		__wusbhc_dev_disable(wusbhc, port_idx);
		break;
	case USB_PORT_FEAT_C_ENABLE:
		wusb_port_by_idx(wusbhc, port_idx)->change &= ~USB_PORT_STAT_C_ENABLE;
		break;
	case USB_PORT_FEAT_SUSPEND:
	case USB_PORT_FEAT_C_SUSPEND:
		dev_err(dev, "(port_idx %d) Clear feat %d/%d UNIMPLEMENTED\n",
			port_idx, feature, selector);
		result = -ENOSYS;
		break;
	default:
		dev_err(dev, "(port_idx %d) Clear feat %d/%d UNKNOWN\n",
			port_idx, feature, selector);
		result = -EPIPE;
		break;
	}
	mutex_unlock(&wusbhc->mutex);

	return result;
}
