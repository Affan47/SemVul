ldns_wire2pkt_hdr(ldns_pkt *packet, const uint8_t *wire, size_t max, size_t *pos)
{
	if (*pos + LDNS_HEADER_SIZE > max) {
		return LDNS_STATUS_WIRE_INCOMPLETE_HEADER;
	} else {
		ldns_pkt_set_id(packet, LDNS_ID_WIRE(wire));
		ldns_pkt_set_qr(packet, LDNS_QR_WIRE(wire));
		ldns_pkt_set_opcode(packet, LDNS_OPCODE_WIRE(wire));
		ldns_pkt_set_aa(packet, LDNS_AA_WIRE(wire));
		ldns_pkt_set_tc(packet, LDNS_TC_WIRE(wire));
		ldns_pkt_set_rd(packet, LDNS_RD_WIRE(wire));
		ldns_pkt_set_ra(packet, LDNS_RA_WIRE(wire));
		ldns_pkt_set_ad(packet, LDNS_AD_WIRE(wire));
		ldns_pkt_set_cd(packet, LDNS_CD_WIRE(wire));
		ldns_pkt_set_rcode(packet, LDNS_RCODE_WIRE(wire));

		ldns_pkt_set_qdcount(packet, LDNS_QDCOUNT(wire));
		ldns_pkt_set_ancount(packet, LDNS_ANCOUNT(wire));
		ldns_pkt_set_nscount(packet, LDNS_NSCOUNT(wire));
		ldns_pkt_set_arcount(packet, LDNS_ARCOUNT(wire));

		*pos += LDNS_HEADER_SIZE;

		return LDNS_STATUS_OK;
	}
}
