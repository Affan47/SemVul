r5l_flush_stripe_to_raid(struct r5l_log *log)
{
	bool do_flush;

	if (!log || !log->need_cache_flush)
		return;

	spin_lock_irq(&log->io_list_lock);

	if (!list_empty(&log->flushing_ios)) {
		spin_unlock_irq(&log->io_list_lock);
		return;
	}
	list_splice_tail_init(&log->io_end_ios, &log->flushing_ios);
	do_flush = !list_empty(&log->flushing_ios);
	spin_unlock_irq(&log->io_list_lock);

	if (!do_flush)
		return;
	bio_reset(&log->flush_bio);
	log->flush_bio.bi_bdev = log->rdev->bdev;
	log->flush_bio.bi_end_io = r5l_log_flush_endio;
	submit_bio(WRITE_FLUSH, &log->flush_bio);
}
