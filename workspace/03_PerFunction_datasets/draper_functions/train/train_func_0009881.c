handle_turn_connect(turn_turnserver *server,
				    ts_ur_super_session *ss, stun_tid *tid,
				    int *err_code, const u08bits **reason, u16bits *unknown_attrs, u16bits *ua_num,
				    ioa_net_data *in_buffer) {

	FUNCSTART;
	ioa_addr peer_addr;
	int peer_found = 0;
	addr_set_any(&peer_addr);
	allocation* a = get_allocation_ss(ss);

	if(!(ss->is_tcp_relay)) {
		*err_code = 403;
		*reason = (const u08bits *)"Connect cannot be used with UDP relay";
	} else if (!is_allocation_valid(a)) {
		*err_code = 437;
		*reason = (const u08bits *)"Allocation mismatch";
	} else {

		stun_attr_ref sar = stun_attr_get_first_str(ioa_network_buffer_data(in_buffer->nbh),
							    ioa_network_buffer_get_size(in_buffer->nbh));
		while (sar && (!(*err_code)) && (*ua_num < MAX_NUMBER_OF_UNKNOWN_ATTRS)) {
			int attr_type = stun_attr_get_type(sar);
			switch (attr_type) {
			SKIP_ATTRIBUTES;
			case STUN_ATTRIBUTE_XOR_PEER_ADDRESS:
			  {
				if(stun_attr_get_addr_str(ioa_network_buffer_data(in_buffer->nbh),
						       ioa_network_buffer_get_size(in_buffer->nbh),
						       sar, &peer_addr,
						       NULL) == -1) {
					*err_code = 400;
					*reason = (const u08bits *)"Bad Peer Address";
				} else {
					if(!get_relay_socket(a,peer_addr.ss.sa_family)) {
						*err_code = 443;
						*reason = (const u08bits *)"Peer Address Family Mismatch";
					}

					peer_found = 1;
				}
				break;
			  }
			default:
				if(attr_type>=0x0000 && attr_type<=0x7FFF)
					unknown_attrs[(*ua_num)++] = nswap16(attr_type);
			};
			sar = stun_attr_get_next_str(ioa_network_buffer_data(in_buffer->nbh),
						     ioa_network_buffer_get_size(in_buffer->nbh),
						     sar);
		}

		if (*ua_num > 0) {

			*err_code = 420;
			*reason = (const u08bits *)"Unknown attribute";

		} else if (*err_code) {

			;

		} else if (!peer_found) {

			*err_code = 400;
			*reason = (const u08bits *)"Where is Peer Address ?";

		} else {
			if(!good_peer_addr(server,ss->realm_options.name,&peer_addr)) {
				*err_code = 403;
				*reason = (const u08bits *) "Forbidden IP";
			} else {
				tcp_start_connection_to_peer(server, ss, tid, a, &peer_addr, err_code, reason);
			}
		}
	}

	FUNCEND;
	return 0;
}
