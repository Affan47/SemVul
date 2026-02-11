dhcpopt_init ( struct dhcp_options *options, void *data, size_t alloc_len,
		    int ( * realloc ) ( struct dhcp_options *options,
					size_t len ) ) {


	options->data = data;
	options->alloc_len = alloc_len;
	options->realloc = realloc;


	dhcpopt_update_used_len ( options );

	DBGC ( options, "DHCPOPT %p created (data %p lengths %#zx,%#zx)\n",
	       options, options->data, options->used_len, options->alloc_len );
}
