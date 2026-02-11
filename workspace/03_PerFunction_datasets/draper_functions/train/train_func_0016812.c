retry_origin_bios(struct dm_snapshot *s, struct bio *bio)
{
	struct bio *n;
	int r;

	while (bio) {
		n = bio->bi_next;
		bio->bi_next = NULL;
		r = do_origin(s->origin, bio);
		if (r == DM_MAPIO_REMAPPED)
			generic_make_request(bio);
		bio = n;
	}
}
