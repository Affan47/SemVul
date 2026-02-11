ldns_rdf2buffer_str_cert_alg(ldns_buffer *output, const ldns_rdf *rdf)
{
        uint16_t data = ldns_read_uint16(ldns_rdf_data(rdf));
	ldns_lookup_table *lt;
 	lt = ldns_lookup_by_id(ldns_cert_algorithms, (int) data);
	if (lt) {
		ldns_buffer_printf(output, "%s", lt->name);
	} else {
		ldns_buffer_printf(output, "%d", data);
	}
	return ldns_buffer_status(output);
}
