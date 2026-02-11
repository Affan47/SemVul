pkt_bio_finished(struct pktcdvd_device *pd)
{
	BUG_ON(atomic_read(&pd->cdrw.pending_bios) <= 0);
	if (atomic_dec_and_test(&pd->cdrw.pending_bios)) {
		pkt_dbg(2, pd, "queue empty\n");
		atomic_set(&pd->iosched.attention, 1);
		wake_up(&pd->wqueue);
	}
}
