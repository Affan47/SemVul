isp1301_get_client(struct device_node *node)
{
	if (node) {
		struct device *dev = bus_find_device(&i2c_bus_type, NULL,
						     node, match);
		if (!dev)
			return NULL;
		return to_i2c_client(dev);
	} else {
		return isp1301_i2c_client;
	}
}
