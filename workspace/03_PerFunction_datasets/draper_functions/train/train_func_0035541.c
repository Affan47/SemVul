nvdimm_bus_uevent(struct device *dev, struct kobj_uevent_env *env)
{


	if (is_nd_pmem(dev) || is_nd_blk(dev))
		set_dev_node(dev, to_nd_region(dev)->numa_node);
	return add_uevent_var(env, "MODALIAS=" ND_DEVICE_MODALIAS_FMT,
			to_nd_device_type(dev));
}
