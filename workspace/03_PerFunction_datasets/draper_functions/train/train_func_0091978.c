gdip_region_bitmap_ensure (GpRegion *region)
{

	if (region->bitmap)
		return;


	region->bitmap = gdip_region_bitmap_from_tree (region->tree);
}
