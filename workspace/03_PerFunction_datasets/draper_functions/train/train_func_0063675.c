dm_rh_dec(struct dm_region_hash *rh, region_t region)
{
	unsigned long flags;
	struct dm_region *reg;
	int should_wake = 0;

	read_lock(&rh->hash_lock);
	reg = __rh_lookup(rh, region);
	read_unlock(&rh->hash_lock);

	spin_lock_irqsave(&rh->region_lock, flags);
	if (atomic_dec_and_test(&reg->pending)) {


		if (unlikely(rh->flush_failure)) {


			reg->state = DM_RH_NOSYNC;
		} else if (reg->state == DM_RH_RECOVERING) {
			list_add_tail(&reg->list, &rh->quiesced_regions);
		} else if (reg->state == DM_RH_DIRTY) {
			reg->state = DM_RH_CLEAN;
			list_add(&reg->list, &rh->clean_regions);
		}
		should_wake = 1;
	}
	spin_unlock_irqrestore(&rh->region_lock, flags);

	if (should_wake)
		rh->wakeup_workers(rh->context);
}
