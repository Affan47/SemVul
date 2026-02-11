fwserial_mgmt_handler(struct fw_card *card,
				  struct fw_request *request,
				  int tcode, int destination, int source,
				  int generation,
				  unsigned long long addr,
				  void *data, size_t len,
				  void *callback_data)
{
	struct fwserial_mgmt_pkt *pkt = data;
	struct fwtty_peer *peer;
	int rcode;

	rcu_read_lock();
	peer = __fwserial_peer_by_node_id(card, generation, source);
	if (!peer) {
		fwtty_dbg(card, "peer(%d:%x) not found\n", generation, source);
		__dump_peer_list(card);
		rcode = RCODE_CONFLICT_ERROR;

	} else {
		switch (tcode) {
		case TCODE_WRITE_BLOCK_REQUEST:
			rcode = fwserial_parse_mgmt_write(peer, pkt, addr, len);
			break;

		default:
			rcode = RCODE_TYPE_ERROR;
		}
	}

	rcu_read_unlock();
	fw_send_response(card, request, rcode);
}
