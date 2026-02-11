find_dhcp_option_with_encap ( struct dhcp_options *options,
					 unsigned int tag,
					 int *encap_offset ) {
	unsigned int original_tag __attribute__ (( unused )) = tag;
	struct dhcp_option *option;
	int offset = 0;
	ssize_t remaining = options->len;
	unsigned int option_len;


	if ( tag == DHCP_PAD )
		return -ENOENT;


	while ( remaining ) {


		option = dhcp_option ( options, offset );
		option_len = dhcp_option_len ( option );
		remaining -= option_len;
		if ( remaining < 0 )
			break;

		if ( option->tag == DHCP_END ) {
			if ( tag == DHCP_END )


				return offset;
			else
				break;
		}

		if ( option->tag == tag ) {
			DBGC ( options, "DHCPOPT %p found %s (length %d)\n",
			       options, dhcp_tag_name ( original_tag ),
			       option_len );
			return offset;
		}

		if ( DHCP_IS_ENCAP_OPT ( tag ) &&
		     ( option->tag == DHCP_ENCAPSULATOR ( tag ) ) ) {
			if ( encap_offset )
				*encap_offset = offset;

			tag = DHCP_ENCAPSULATED ( tag );
			remaining = option_len;
			offset += DHCP_OPTION_HEADER_LEN;
			continue;
		}
		offset += option_len;
	}

	return -ENOENT;
}
