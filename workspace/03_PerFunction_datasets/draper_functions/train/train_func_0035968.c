hib_wait_io(struct hib_bio_batch *hb)
{
	wait_event(hb->wait, atomic_read(&hb->count) == 0);
	return hb->error;
}
