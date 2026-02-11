ldns_rdf2buffer_str_nsec3_salt(ldns_buffer *output, const ldns_rdf *rdf)
{
	uint8_t salt_length;
	uint8_t salt_pos;

	uint8_t *data = ldns_rdf_data(rdf);

        if(ldns_rdf_size(rdf) < 1) {
                return LDNS_STATUS_WIRE_RDATA_ERR;
        }
	salt_length = data[0];

	if (salt_length == 0 || ((size_t)salt_length)+1 > ldns_rdf_size(rdf)) {
		ldns_buffer_printf(output, "- ");
	} else {
		for (salt_pos = 0; salt_pos < salt_length; salt_pos++) {
			ldns_buffer_printf(output, "%02x", data[1 + salt_pos]);
		}
		ldns_buffer_printf(output, " ");
	}

	return ldns_buffer_status(output);
}
