regmap_async_complete(struct regmap *map)
{
	unsigned long flags;
	int ret;


	if (!map->bus || !map->bus->async_write)
		return 0;

	trace_regmap_async_complete_start(map);

	wait_event(map->async_waitq, regmap_async_is_done(map));

	spin_lock_irqsave(&map->async_lock, flags);
	ret = map->async_ret;
	map->async_ret = 0;
	spin_unlock_irqrestore(&map->async_lock, flags);

	trace_regmap_async_complete_done(map);

	return ret;
}
