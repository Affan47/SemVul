check_low_water_mark(struct pool *pool, dm_block_t free_blocks)
{
	unsigned long flags;

	if (free_blocks <= pool->low_water_blocks && !pool->low_water_triggered) {
		DMWARN("%s: reached low water mark for data device: sending event.",
		       dm_device_name(pool->pool_md));
		spin_lock_irqsave(&pool->lock, flags);
		pool->low_water_triggered = true;
		spin_unlock_irqrestore(&pool->lock, flags);
		dm_table_event(pool->ti->table);
	}
}
