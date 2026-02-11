iot_update_stats(struct io_tracker *t, struct bio *bio)
{
	if (bio->bi_iter.bi_sector == from_oblock(t->last_end_oblock) + 1)
		t->nr_seq_samples++;
	else {


		if (t->nr_seq_samples) {
			t->nr_seq_samples = 0;
			t->nr_rand_samples = 0;
		}

		t->nr_rand_samples++;
	}

	t->last_end_oblock = to_oblock(bio_end_sector(bio) - 1);
}
