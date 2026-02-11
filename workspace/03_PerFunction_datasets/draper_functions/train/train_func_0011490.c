ldns_pkt_free(ldns_pkt *packet)
{
	if (packet) {
		LDNS_FREE(packet->_header);
		ldns_rr_list_deep_free(packet->_question);
		ldns_rr_list_deep_free(packet->_answer);
		ldns_rr_list_deep_free(packet->_authority);
		ldns_rr_list_deep_free(packet->_additional);
		ldns_rr_free(packet->_tsig_rr);
		ldns_rdf_deep_free(packet->_edns_data);
		ldns_rdf_deep_free(packet->_answerfrom);
		LDNS_FREE(packet);
	}
}
