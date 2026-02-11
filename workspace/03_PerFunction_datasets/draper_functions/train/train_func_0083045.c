receive_DataReply(struct drbd_connection *connection, struct packet_info *pi)
{
	struct drbd_peer_device *peer_device;
	struct drbd_device *device;
	struct drbd_request *req;
	sector_t sector;
	int err;
	struct p_data *p = pi->data;

	peer_device = conn_peer_device(connection, pi->vnr);
	if (!peer_device)
		return -EIO;
	device = peer_device->device;

	sector = be64_to_cpu(p->sector);

	spin_lock_irq(&device->resource->req_lock);
	req = find_request(device, &device->read_requests, p->block_id, sector, false, __func__);
	spin_unlock_irq(&device->resource->req_lock);
	if (unlikely(!req))
		return -EIO;


	err = recv_dless_read(peer_device, req, sector, pi->size);
	if (!err)
		req_mod(req, DATA_RECEIVED);


	return err;
}
