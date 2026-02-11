read_callback(unsigned long error, void *context)
{
	struct bio *bio = context;
	struct mirror *m;

	m = bio_get_m(bio);
	bio_set_m(bio, NULL);

	if (likely(!error)) {
		bio_endio(bio);
		return;
	}

	fail_mirror(m, DM_RAID1_READ_ERROR);

	if (likely(default_ok(m)) || mirror_available(m->ms, bio)) {
		DMWARN_LIMIT("Read failure on mirror device %s.  "
			     "Trying alternative device.",
			     m->dev->name);
		queue_bio(m->ms, bio, bio_rw(bio));
		return;
	}

	DMERR_LIMIT("Read failure on mirror device %s.  Failing I/O.",
		    m->dev->name);
	bio_io_error(bio);
}
