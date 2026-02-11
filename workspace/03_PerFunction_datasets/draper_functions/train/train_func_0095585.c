metric_id_get(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct mrvl_mesh_defaults defs;
	int ret;

	ret = mesh_get_default_parameters(dev, &defs);

	if (ret)
		return ret;

	return snprintf(buf, 5, "%d\n", defs.meshie.val.active_metric_id);
}
