drbd_submit_req_private_bio(struct drbd_request *req)
{
	struct drbd_device *device = req->device;
	struct bio *bio = req->private_bio;
	const int rw = bio_rw(bio);

	bio->bi_bdev = device->ldev->backing_bdev;


	if (get_ldev(device)) {
		req->pre_submit_jif = jiffies;
		if (drbd_insert_fault(device,
				      rw == WRITE ? DRBD_FAULT_DT_WR
				    : rw == READ  ? DRBD_FAULT_DT_RD
				    :               DRBD_FAULT_DT_RA))
			bio_io_error(bio);
		else
			generic_make_request(bio);
		put_ldev(device);
	} else
		bio_io_error(bio);
}
