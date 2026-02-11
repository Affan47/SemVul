drbd_send_drequest(struct drbd_peer_device *peer_device, int cmd,
		       sector_t sector, int size, u64 block_id)
{
	struct drbd_socket *sock;
	struct p_block_req *p;

	sock = &peer_device->connection->data;
	p = drbd_prepare_command(peer_device, sock);
	if (!p)
		return -EIO;
	p->sector = cpu_to_be64(sector);
	p->block_id = block_id;
	p->blksize = cpu_to_be32(size);
	return drbd_send_command(peer_device, sock, cmd, sizeof(*p), NULL, 0);
}
