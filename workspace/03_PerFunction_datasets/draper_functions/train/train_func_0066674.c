drbd_debugfs_peer_device_add(struct drbd_peer_device *peer_device)
{
	struct dentry *conn_dir = peer_device->connection->debugfs_conn;
	struct dentry *dentry;
	char vnr_buf[8];

	if (!conn_dir)
		return;

	snprintf(vnr_buf, sizeof(vnr_buf), "%u", peer_device->device->vnr);
	dentry = debugfs_create_dir(vnr_buf, conn_dir);
	if (IS_ERR_OR_NULL(dentry))
		goto fail;
	peer_device->debugfs_peer_dev = dentry;
	return;

fail:
	drbd_debugfs_peer_device_cleanup(peer_device);
	drbd_err(peer_device, "failed to create debugfs entries\n");
}
