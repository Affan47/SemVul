__fwtty_write_port_status(struct fwtty_port *port)
{
	struct fwtty_peer *peer;
	int err = -ENOENT;
	unsigned status = __fwtty_port_line_status(port);

	rcu_read_lock();
	peer = rcu_dereference(port->peer);
	if (peer) {
		err = fwtty_send_data_async(peer, TCODE_WRITE_QUADLET_REQUEST,
					    peer->status_addr, &status,
					    sizeof(status), NULL, port);
	}
	rcu_read_unlock();

	return err;
}
