__mlx4_find_zone_by_uid_unique(
		struct mlx4_zone_allocator *zones, u32 obj)
{
	struct mlx4_zone_entry *zone, *zone_candidate = NULL;
	u32 dist = (u32)-1;


	list_for_each_entry(zone, &zones->entries, list) {
		if (obj >= zone->offset) {
			u32 mobj = (obj - zone->offset) & zones->mask;

			if (mobj < zone->bitmap->max) {
				u32 curr_dist = zone->bitmap->effective_len;

				if (curr_dist < dist) {
					dist = curr_dist;
					zone_candidate = zone;
				}
			}
		}
	}

	return zone_candidate;
}
