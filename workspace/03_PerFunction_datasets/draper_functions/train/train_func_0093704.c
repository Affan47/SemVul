drbd_endio_write_sec_final(struct drbd_peer_request *peer_req) __releases(local)
{
	unsigned long flags = 0;
	struct drbd_peer_device *peer_device = peer_req->peer_device;
	struct drbd_device *device = peer_device->device;
	struct drbd_interval i;
	int do_wake;
	u64 block_id;
	int do_al_complete_io;


	i = peer_req->i;
	do_al_complete_io = peer_req->flags & EE_CALL_AL_COMPLETE_IO;
	block_id = peer_req->block_id;
	peer_req->flags &= ~EE_CALL_AL_COMPLETE_IO;

	spin_lock_irqsave(&device->resource->req_lock, flags);
	device->writ_cnt += peer_req->i.size >> 9;
	list_move_tail(&peer_req->w.list, &device->done_ee);


	do_wake = list_empty(block_id == ID_SYNCER ? &device->sync_ee : &device->active_ee);


	if (peer_req->flags & EE_WAS_ERROR)
		__drbd_chk_io_error(device, DRBD_WRITE_ERROR);
	spin_unlock_irqrestore(&device->resource->req_lock, flags);

	if (block_id == ID_SYNCER)
		drbd_rs_complete_io(device, i.sector);

	if (do_wake)
		wake_up(&device->ee_wait);

	if (do_al_complete_io)
		drbd_al_complete_io(device, &i);

	wake_asender(peer_device->connection);
	put_ldev(device);
}
