raid1_end_write_request(struct bio *bio)
{
	struct r1bio *r1_bio = bio->bi_private;
	int mirror, behind = test_bit(R1BIO_BehindIO, &r1_bio->state);
	struct r1conf *conf = r1_bio->mddev->private;
	struct bio *to_put = NULL;

	mirror = find_bio_disk(r1_bio, bio);


	if (bio->bi_error) {
		set_bit(WriteErrorSeen,
			&conf->mirrors[mirror].rdev->flags);
		if (!test_and_set_bit(WantReplacement,
				      &conf->mirrors[mirror].rdev->flags))
			set_bit(MD_RECOVERY_NEEDED, &
				conf->mddev->recovery);

		set_bit(R1BIO_WriteError, &r1_bio->state);
	} else {


		sector_t first_bad;
		int bad_sectors;

		r1_bio->bios[mirror] = NULL;
		to_put = bio;


		if (test_bit(In_sync, &conf->mirrors[mirror].rdev->flags) &&
		    !test_bit(Faulty, &conf->mirrors[mirror].rdev->flags))
			set_bit(R1BIO_Uptodate, &r1_bio->state);


		if (is_badblock(conf->mirrors[mirror].rdev,
				r1_bio->sector, r1_bio->sectors,
				&first_bad, &bad_sectors)) {
			r1_bio->bios[mirror] = IO_MADE_GOOD;
			set_bit(R1BIO_MadeGood, &r1_bio->state);
		}
	}

	if (behind) {
		if (test_bit(WriteMostly, &conf->mirrors[mirror].rdev->flags))
			atomic_dec(&r1_bio->behind_remaining);


		if (atomic_read(&r1_bio->behind_remaining) >= (atomic_read(&r1_bio->remaining)-1) &&
		    test_bit(R1BIO_Uptodate, &r1_bio->state)) {

			if (!test_and_set_bit(R1BIO_Returned, &r1_bio->state)) {
				struct bio *mbio = r1_bio->master_bio;
				pr_debug("raid1: behind end write sectors"
					 " %llu-%llu\n",
					 (unsigned long long) mbio->bi_iter.bi_sector,
					 (unsigned long long) bio_end_sector(mbio) - 1);
				call_bio_endio(r1_bio);
			}
		}
	}
	if (r1_bio->bios[mirror] == NULL)
		rdev_dec_pending(conf->mirrors[mirror].rdev,
				 conf->mddev);


	r1_bio_write_done(r1_bio);

	if (to_put)
		bio_put(to_put);
}
