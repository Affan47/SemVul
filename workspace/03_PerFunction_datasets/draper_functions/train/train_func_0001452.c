to_nd_blk_region(struct device *dev)
{
	struct nd_region *nd_region = to_nd_region(dev);

	WARN_ON(!is_nd_blk(dev));
	return container_of(nd_region, struct nd_blk_region, nd_region);
}
