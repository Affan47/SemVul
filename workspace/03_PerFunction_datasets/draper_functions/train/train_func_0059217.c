fbtft_of_value(struct device_node *node, const char *propname)
{
	int ret;
	u32 val = 0;

	ret = of_property_read_u32(node, propname, &val);
	if (ret == 0)
		pr_info("%s: %s = %u\n", __func__, propname, val);

	return val;
}
