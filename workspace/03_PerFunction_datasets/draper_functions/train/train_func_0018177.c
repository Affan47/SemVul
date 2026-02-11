got_NegAck(struct drbd_connection *connection, struct packet_info *pi)
{
	struct drbd_peer_device *peer_device;
	struct drbd_device *device;
	struct p_block_ack *p = pi->data;
	sector_t sector = be64_to_cpu(p->sector);
	int size = be32_to_cpu(p->blksize);
	int err;

	peer_device = conn_peer_device(connection, pi->vnr);
	if (!peer_device)
		return -EIO;
	device = peer_device->device;

	update_peer_seq(peer_device, be32_to_cpu(p->seq_num));

	if (p->block_id == ID_SYNCER) {
		dec_rs_pending(device);
		drbd_rs_failed_io(device, sector, size);
		return 0;
	}

	err = validate_req_change_req_state(device, p->block_id, sector,
					    &device->write_requests, __func__,
					    NEG_ACKED, true);
	if (err) {


		drbd_set_out_of_sync(device, sector, size);
	}
	return 0;
}
