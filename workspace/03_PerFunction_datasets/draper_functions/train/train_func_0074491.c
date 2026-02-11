fwserial_handle_unplug_req(struct work_struct *work)
{
	struct fwtty_peer *peer = to_peer(work, work);
	struct fwtty_port *port = NULL;
	struct fwserial_mgmt_pkt *pkt;
	int rcode;

	pkt = kmalloc(sizeof(*pkt), GFP_KERNEL);
	if (!pkt)
		return;

	spin_lock_bh(&peer->lock);

	switch (peer->state) {
	case FWPS_ATTACHED:
		fill_unplug_rsp_ok(pkt);
		peer_set_state(peer, FWPS_UNPLUG_RESPONDING);
		break;

	case FWPS_UNPLUG_PENDING:
		if (peer->serial->card->guid > peer->guid)
			goto cleanup;


		del_timer(&peer->timer);
		fill_unplug_rsp_ok(pkt);
		peer_set_state(peer, FWPS_UNPLUG_RESPONDING);
		break;

	default:
		fill_unplug_rsp_nack(pkt);
	}

	spin_unlock_bh(&peer->lock);

	rcode = fwserial_send_mgmt_sync(peer, pkt);

	spin_lock_bh(&peer->lock);
	if (peer->state == FWPS_UNPLUG_RESPONDING) {
		if (rcode != RCODE_COMPLETE)
			fwtty_err(&peer->unit, "UNPLUG_RSP error (%d)\n",
				  rcode);
		port = peer_revert_state(peer);
	}
cleanup:
	spin_unlock_bh(&peer->lock);
	if (port)
		fwserial_release_port(port, true);
	kfree(pkt);
}
