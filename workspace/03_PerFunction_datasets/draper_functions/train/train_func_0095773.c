ttm_check_swapping(struct ttm_mem_global *glob)
{
	bool needs_swapping = false;
	unsigned int i;
	struct ttm_mem_zone *zone;

	spin_lock(&glob->lock);
	for (i = 0; i < glob->num_zones; ++i) {
		zone = glob->zones[i];
		if (zone->used_mem > zone->swap_limit) {
			needs_swapping = true;
			break;
		}
	}

	spin_unlock(&glob->lock);

	if (unlikely(needs_swapping))
		(void)queue_work(glob->swap_queue, &glob->work);

}
