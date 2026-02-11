rt9455_usb_event(struct notifier_block *nb,
			    unsigned long event, void *power)
{
	struct rt9455_info *info = container_of(nb, struct rt9455_info, nb);
	struct device *dev = &info->client->dev;
	unsigned int opa_mode, iaicr;
	int ret;


	ret = regmap_field_read(info->regmap_fields[F_OPA_MODE],
				&opa_mode);
	if (ret) {
		dev_err(dev, "Failed to read OPA_MODE value\n");
		return NOTIFY_DONE;
	}

	ret = regmap_field_read(info->regmap_fields[F_IAICR],
				&iaicr);
	if (ret) {
		dev_err(dev, "Failed to read IAICR value\n");
		return NOTIFY_DONE;
	}

	dev_dbg(dev, "Received USB event %lu\n", event);
	switch (event) {
	case USB_EVENT_NONE:
		return rt9455_usb_event_none(info, opa_mode, iaicr);
	case USB_EVENT_VBUS:
		return rt9455_usb_event_vbus(info, opa_mode, iaicr);
	case USB_EVENT_ID:
		return rt9455_usb_event_id(info, opa_mode, iaicr);
	case USB_EVENT_CHARGER:
		return rt9455_usb_event_charger(info, opa_mode, iaicr);
	default:
		dev_err(dev, "Unknown USB event\n");
	}
	return NOTIFY_DONE;
}
