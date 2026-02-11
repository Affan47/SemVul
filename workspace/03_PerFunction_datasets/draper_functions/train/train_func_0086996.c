is_idle(struct device *dev, struct nd_namespace_common *ndns)
{
	struct nd_region *nd_region = to_nd_region(dev->parent);
	struct device *seed = NULL;

	if (is_nd_btt(dev))
		seed = nd_region->btt_seed;
	else if (is_nd_pfn(dev))
		seed = nd_region->pfn_seed;

	if (seed == dev || ndns || dev->driver)
		return false;
	return true;
}
