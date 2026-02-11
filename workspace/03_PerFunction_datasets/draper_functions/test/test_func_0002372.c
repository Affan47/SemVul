am335x_get_phy_control(struct device *dev)
{
	struct device_node *node;
	struct am335x_control_usb *ctrl_usb;

	node = of_parse_phandle(dev->of_node, "ti,ctrl_mod", 0);
	if (!node)
		return NULL;

	dev = bus_find_device(&platform_bus_type, NULL, node, match);
	of_node_put(node);
	if (!dev)
		return NULL;

	ctrl_usb = dev_get_drvdata(dev);
	put_device(dev);
	if (!ctrl_usb)
		return NULL;
	return &ctrl_usb->phy_ctrl;
}
