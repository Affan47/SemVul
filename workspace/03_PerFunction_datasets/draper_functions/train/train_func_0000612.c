pkt_iosched_process_queue(struct pktcdvd_device *pd)
{

	if (atomic_read(&pd->iosched.attention) == 0)
		return;
	atomic_set(&pd->iosched.attention, 0);

	for (;;) {
		struct bio *bio;
		int reads_queued, writes_queued;

		spin_lock(&pd->iosched.lock);
		reads_queued = !bio_list_empty(&pd->iosched.read_queue);
		writes_queued = !bio_list_empty(&pd->iosched.write_queue);
		spin_unlock(&pd->iosched.lock);

		if (!reads_queued && !writes_queued)
			break;

		if (pd->iosched.writing) {
			int need_write_seek = 1;
			spin_lock(&pd->iosched.lock);
			bio = bio_list_peek(&pd->iosched.write_queue);
			spin_unlock(&pd->iosched.lock);
			if (bio && (bio->bi_iter.bi_sector ==
				    pd->iosched.last_write))
				need_write_seek = 0;
			if (need_write_seek && reads_queued) {
				if (atomic_read(&pd->cdrw.pending_bios) > 0) {
					pkt_dbg(2, pd, "write, waiting\n");
					break;
				}
				pkt_flush_cache(pd);
				pd->iosched.writing = 0;
			}
		} else {
			if (!reads_queued && writes_queued) {
				if (atomic_read(&pd->cdrw.pending_bios) > 0) {
					pkt_dbg(2, pd, "read, waiting\n");
					break;
				}
				pd->iosched.writing = 1;
			}
		}

		spin_lock(&pd->iosched.lock);
		if (pd->iosched.writing)
			bio = bio_list_pop(&pd->iosched.write_queue);
		else
			bio = bio_list_pop(&pd->iosched.read_queue);
		spin_unlock(&pd->iosched.lock);

		if (!bio)
			continue;

		if (bio_data_dir(bio) == READ)
			pd->iosched.successive_reads +=
				bio->bi_iter.bi_size >> 10;
		else {
			pd->iosched.successive_reads = 0;
			pd->iosched.last_write = bio_end_sector(bio);
		}
		if (pd->iosched.successive_reads >= HI_SPEED_SWITCH) {
			if (pd->read_speed == pd->write_speed) {
				pd->read_speed = MAX_SPEED;
				pkt_set_speed(pd, pd->write_speed, pd->read_speed);
			}
		} else {
			if (pd->read_speed != pd->write_speed) {
				pd->read_speed = pd->write_speed;
				pkt_set_speed(pd, pd->write_speed, pd->read_speed);
			}
		}

		atomic_inc(&pd->cdrw.pending_bios);
		generic_make_request(bio);
	}
}
