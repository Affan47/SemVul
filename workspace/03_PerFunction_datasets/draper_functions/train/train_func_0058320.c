call_bio_endio(struct r1bio *r1_bio)
{
	struct bio *bio = r1_bio->master_bio;
	int done;
	struct r1conf *conf = r1_bio->mddev->private;
	sector_t start_next_window = r1_bio->start_next_window;
	sector_t bi_sector = bio->bi_iter.bi_sector;

	if (bio->bi_phys_segments) {
		unsigned long flags;
		spin_lock_irqsave(&conf->device_lock, flags);
		bio->bi_phys_segments--;
		done = (bio->bi_phys_segments == 0);
		spin_unlock_irqrestore(&conf->device_lock, flags);


		wake_up(&conf->wait_barrier);
	} else
		done = 1;

	if (!test_bit(R1BIO_Uptodate, &r1_bio->state))
		bio->bi_error = -EIO;

	if (done) {
		bio_endio(bio);


		allow_barrier(conf, start_next_window, bi_sector);
	}
}
