gdip_is_region_empty (GpRegion *region)
{
	GpRectF rect;

	if (!region)
		return FALSE;

	if (region->type == RegionTypePath) {

		if (!region->tree)
			return TRUE;
		if (region->tree->path)
			return (region->tree->path->count == 0);
		return FALSE;
	}

	if (!region->rects || (region->cnt == 0))
		return TRUE;

	gdip_get_bounds (region->rects, region->cnt, &rect);
	return ((rect.Width == 0) || (rect.Height == 0));
}
