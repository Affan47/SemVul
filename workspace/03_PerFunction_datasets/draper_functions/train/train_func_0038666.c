got_OVResult(struct drbd_connection *connection, struct packet_info *pi)
{
	struct drbd_peer_device *peer_device;
	struct drbd_device *device;
	struct p_block_ack *p = pi->data;
	struct drbd_device_work *dw;
	sector_t sector;
	int size;

	peer_device = conn_peer_device(connection, pi->vnr);
	if (!peer_device)
		return -EIO;
	device = peer_device->device;

	sector = be64_to_cpu(p->sector);
	size = be32_to_cpu(p->blksize);

	update_peer_seq(peer_device, be32_to_cpu(p->seq_num));

	if (be64_to_cpu(p->block_id) == ID_OUT_OF_SYNC)
		drbd_ov_out_of_sync_found(device, sector, size);
	else
		ov_out_of_sync_print(device);

	if (!get_ldev(device))
		return 0;

	drbd_rs_complete_io(device, sector);
	dec_rs_pending(device);

	--device->ov_left;


	if ((device->ov_left & 0x200) == 0x200)
		drbd_advance_rs_marks(device, device->ov_left);

	if (device->ov_left == 0) {
		dw = kmalloc(sizeof(*dw), GFP_NOIO);
		if (dw) {
			dw->w.cb = w_ov_finished;
			dw->device = device;
			drbd_queue_work(&peer_device->connection->sender_work, &dw->w);
		} else {
			drbd_err(device, "kmalloc(dw) failed.");
			ov_out_of_sync_print(device);
			drbd_resync_finished(device);
		}
	}
	put_ldev(device);
	return 0;
}
