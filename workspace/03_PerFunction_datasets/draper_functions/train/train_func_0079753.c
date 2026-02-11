drbd_peer_request_endio(struct bio *bio)
{
	struct drbd_peer_request *peer_req = bio->bi_private;
	struct drbd_device *device = peer_req->peer_device->device;
	int is_write = bio_data_dir(bio) == WRITE;
	int is_discard = !!(bio->bi_rw & REQ_DISCARD);

	if (bio->bi_error && __ratelimit(&drbd_ratelimit_state))
		drbd_warn(device, "%s: error=%d s=%llus\n",
				is_write ? (is_discard ? "discard" : "write")
					: "read", bio->bi_error,
				(unsigned long long)peer_req->i.sector);

	if (bio->bi_error)
		set_bit(__EE_WAS_ERROR, &peer_req->flags);

	bio_put(bio);
	if (atomic_dec_and_test(&peer_req->pending_bios)) {
		if (is_write)
			drbd_endio_write_sec_final(peer_req);
		else
			drbd_endio_read_sec_final(peer_req);
	}
}
