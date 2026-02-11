set_if_null_req_ack_pending(struct drbd_peer_device *peer_device, struct drbd_request *req)
{
	struct drbd_connection *connection = peer_device ? peer_device->connection : NULL;
	if (!connection)
		return;
	if (connection->req_ack_pending == NULL)
		connection->req_ack_pending = req;
}
