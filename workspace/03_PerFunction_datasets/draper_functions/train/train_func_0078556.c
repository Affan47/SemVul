dhcp_option_len ( struct dhcp_option *option ) {
	if ( ( option->tag == DHCP_END ) || ( option->tag == DHCP_PAD ) ) {
		return 1;
	} else {
		return ( option->len + DHCP_OPTION_HEADER_LEN );
	}
}
