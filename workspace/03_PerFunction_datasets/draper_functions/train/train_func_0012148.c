bitmap_end_sync(struct bitmap *bitmap, sector_t offset, sector_t *blocks, int aborted)
{
	bitmap_counter_t *bmc;
	unsigned long flags;

	if (bitmap == NULL) {
		*blocks = 1024;
		return;
	}
	spin_lock_irqsave(&bitmap->counts.lock, flags);
	bmc = bitmap_get_counter(&bitmap->counts, offset, blocks, 0);
	if (bmc == NULL)
		goto unlock;

	if (RESYNC(*bmc)) {
		*bmc &= ~RESYNC_MASK;

		if (!NEEDED(*bmc) && aborted)
			*bmc |= NEEDED_MASK;
		else {
			if (*bmc <= 2) {
				bitmap_set_pending(&bitmap->counts, offset);
				bitmap->allclean = 0;
			}
		}
	}
 unlock:
	spin_unlock_irqrestore(&bitmap->counts.lock, flags);
}
