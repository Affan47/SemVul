vgt_balloon_space(struct drm_mm *mm,
			     struct drm_mm_node *node,
			     unsigned long start, unsigned long end)
{
	unsigned long size = end - start;

	if (start == end)
		return -EINVAL;

	DRM_INFO("balloon space: range [ 0x%lx - 0x%lx ] %lu KiB.\n",
		 start, end, size / 1024);

	node->start = start;
	node->size = size;

	return drm_mm_reserve_node(mm, node);
}
