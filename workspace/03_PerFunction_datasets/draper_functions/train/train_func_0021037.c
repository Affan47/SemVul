__rh_recovery_prepare(struct dm_region_hash *rh)
{
	int r;
	region_t region;
	struct dm_region *reg;


	r = rh->log->type->get_resync_work(rh->log, &region);
	if (r <= 0)
		return r;


	read_lock(&rh->hash_lock);
	reg = __rh_find(rh, region);
	read_unlock(&rh->hash_lock);

	spin_lock_irq(&rh->region_lock);
	reg->state = DM_RH_RECOVERING;


	if (atomic_read(&reg->pending))
		list_del_init(&reg->list);
	else
		list_move(&reg->list, &rh->quiesced_regions);

	spin_unlock_irq(&rh->region_lock);

	return 1;
}
