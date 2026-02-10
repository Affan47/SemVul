ldns_pkt_new(void)
{
	ldns_pkt *packet;
	packet = LDNS_MALLOC(ldns_pkt);
	if (!packet) {
		return NULL;
	}

	packet->_header = LDNS_MALLOC(ldns_hdr);
	if (!packet->_header) {
		LDNS_FREE(packet);
		return NULL;
	}

	packet->_question = ldns_rr_list_new();
	packet->_answer = ldns_rr_list_new();
	packet->_authority = ldns_rr_list_new();
	packet->_additional = ldns_rr_list_new();


	ldns_pkt_set_qr(packet, false);
	ldns_pkt_set_aa(packet, false);
	ldns_pkt_set_tc(packet, false);
	ldns_pkt_set_rd(packet, false);
	ldns_pkt_set_ra(packet, false);
	ldns_pkt_set_ad(packet, false);
	ldns_pkt_set_cd(packet, false);

	ldns_pkt_set_opcode(packet, LDNS_PACKET_QUERY);
	ldns_pkt_set_rcode(packet, 0);
	ldns_pkt_set_id(packet, 0);
	ldns_pkt_set_size(packet, 0);
	ldns_pkt_set_querytime(packet, 0);
	memset(&packet->timestamp, 0, sizeof(packet->timestamp));
	ldns_pkt_set_answerfrom(packet, NULL);
	ldns_pkt_set_section_count(packet, LDNS_SECTION_QUESTION, 0);
	ldns_pkt_set_section_count(packet, LDNS_SECTION_ANSWER, 0);
	ldns_pkt_set_section_count(packet, LDNS_SECTION_AUTHORITY, 0);
	ldns_pkt_set_section_count(packet, LDNS_SECTION_ADDITIONAL, 0);

	ldns_pkt_set_edns_udp_size(packet, 0);
	ldns_pkt_set_edns_extended_rcode(packet, 0);
	ldns_pkt_set_edns_version(packet, 0);
	ldns_pkt_set_edns_z(packet, 0);
	ldns_pkt_set_edns_data(packet, NULL);

	ldns_pkt_set_tsig(packet, NULL);

	return packet;
}
