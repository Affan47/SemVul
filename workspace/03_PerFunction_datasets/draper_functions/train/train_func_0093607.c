fwnode_property_read_string(struct fwnode_handle *fwnode,
				const char *propname, const char **val)
{
	int ret;

	ret = __fwnode_property_read_string(fwnode, propname, val);
	if (ret == -EINVAL && fwnode->secondary)
		ret = __fwnode_property_read_string(fwnode->secondary,
						    propname, val);
	return ret;
}
