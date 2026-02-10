ldns_axfr_next(ldns_resolver *resolver)
{
	ldns_rr *cur_rr;
	uint8_t *packet_wire;
	size_t packet_wire_size;
	ldns_lookup_table *rcode;
	ldns_status status;


	if (!resolver || resolver->_socket == 0) {
		return NULL;
	}

	if (resolver->_cur_axfr_pkt) {
		if (resolver->_axfr_i == ldns_pkt_ancount(resolver->_cur_axfr_pkt)) {
			ldns_pkt_free(resolver->_cur_axfr_pkt);
			resolver->_cur_axfr_pkt = NULL;
			return ldns_axfr_next(resolver);
		}
		cur_rr = ldns_rr_clone(ldns_rr_list_rr(
					ldns_pkt_answer(resolver->_cur_axfr_pkt),
					resolver->_axfr_i));
		resolver->_axfr_i++;
		if (ldns_rr_get_type(cur_rr) == LDNS_RR_TYPE_SOA) {
			resolver->_axfr_soa_count++;
			if (resolver->_axfr_soa_count >= 2) {
#ifndef USE_WINSOCK
				close(resolver->_socket);
#else
				closesocket(resolver->_socket);
#endif
				resolver->_socket = 0;
				ldns_pkt_free(resolver->_cur_axfr_pkt);
				resolver->_cur_axfr_pkt = NULL;
			}
		}
		return cur_rr;
	} else {
		packet_wire = ldns_tcp_read_wire(resolver->_socket, &packet_wire_size);
		if(!packet_wire)
			return NULL;

		status = ldns_wire2pkt(&resolver->_cur_axfr_pkt, packet_wire,
				     packet_wire_size);
		LDNS_FREE(packet_wire);

		resolver->_axfr_i = 0;
		if (status != LDNS_STATUS_OK) {

#ifdef STDERR_MSGS
			fprintf(stderr, "Error parsing rr during AXFR: %s\n", ldns_get_errorstr_by_id(status));
#endif


#ifndef USE_WINSOCK
			close(resolver->_socket);
#else
			closesocket(resolver->_socket);
#endif
			resolver->_socket = 0;

			return NULL;
		} else if (ldns_pkt_get_rcode(resolver->_cur_axfr_pkt) != 0) {
			rcode = ldns_lookup_by_id(ldns_rcodes, (int) ldns_pkt_get_rcode(resolver->_cur_axfr_pkt));
#ifdef STDERR_MSGS
			if (rcode) {
				fprintf(stderr, "Error in AXFR: %s\n",
						rcode->name);
			} else {
				fprintf(stderr, "Error in AXFR: %d\n",
						(int) ldns_pkt_get_rcode(
						resolver->_cur_axfr_pkt));
			}
#endif


#ifndef USE_WINSOCK
			close(resolver->_socket);
#else
			closesocket(resolver->_socket);
#endif
			resolver->_socket = 0;

			return NULL;
		} else {
			return ldns_axfr_next(resolver);
		}

	}

}
