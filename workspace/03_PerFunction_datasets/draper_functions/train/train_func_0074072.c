mlx4_zone_add_one(struct mlx4_zone_allocator *zone_alloc,
		      struct mlx4_bitmap *bitmap,
		      u32 flags,
		      int priority,
		      int offset,
		      u32 *puid)
{
	u32 mask = mlx4_bitmap_masked_value(bitmap, (u32)-1);
	struct mlx4_zone_entry *it;
	struct mlx4_zone_entry *zone = kmalloc(sizeof(*zone), GFP_KERNEL);

	if (NULL == zone)
		return -ENOMEM;

	zone->flags = flags;
	zone->bitmap = bitmap;
	zone->use_rr = (flags & MLX4_ZONE_USE_RR) ? MLX4_USE_RR : 0;
	zone->priority = priority;
	zone->offset = offset;

	spin_lock(&zone_alloc->lock);

	zone->uid = zone_alloc->last_uid++;
	zone->allocator = zone_alloc;

	if (zone_alloc->mask < mask)
		zone_alloc->mask = mask;

	list_for_each_entry(it, &zone_alloc->prios, prio_list)
		if (it->priority >= priority)
			break;

	if (&it->prio_list == &zone_alloc->prios || it->priority > priority)
		list_add_tail(&zone->prio_list, &it->prio_list);
	list_add_tail(&zone->list, &it->list);

	spin_unlock(&zone_alloc->lock);

	*puid = zone->uid;

	return 0;
}
