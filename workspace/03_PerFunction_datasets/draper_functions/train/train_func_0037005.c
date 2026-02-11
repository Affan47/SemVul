init_filters(struct filters *filters){
	memset(filters, 0, sizeof(struct filters));

	if( (filters->blocksrc= malloc(sizeof(struct in6_addr) * MAX_BLOCK_SRC)) == NULL)
		return(-1);

	if( (filters->blockdst= malloc(sizeof(struct in6_addr) * MAX_BLOCK_DST)) == NULL)
		return(-1);

	if( (filters->blocktarget= malloc(sizeof(struct in6_addr) * MAX_BLOCK_TARGET)) == NULL)
		return(-1);

	if( (filters->blocklinksrc= malloc(sizeof(struct ether_addr) * MAX_BLOCK_LINK_SRC)) == NULL)
		return(-1);

	if( (filters->blocklinkdst= malloc(sizeof(struct ether_addr) * MAX_BLOCK_LINK_DST)) == NULL)
		return(-1);

	if( (filters->blocksrclen= malloc(sizeof(u_int8_t) * MAX_BLOCK_SRC)) == NULL)
		return(-1);

	if( (filters->blockdstlen= malloc(sizeof(u_int8_t) * MAX_BLOCK_DST)) == NULL)
		return(-1);

	if( (filters->blocktargetlen= malloc(sizeof(u_int8_t) * MAX_BLOCK_TARGET)) == NULL)
		return(-1);

	if( (filters->acceptsrc= malloc(sizeof(struct in6_addr) * MAX_ACCEPT_SRC)) == NULL)
		return(-1);

	if( (filters->acceptdst= malloc(sizeof(struct in6_addr) * MAX_ACCEPT_DST)) == NULL)
		return(-1);

	if( (filters->accepttarget= malloc(sizeof(struct in6_addr) * MAX_ACCEPT_TARGET)) == NULL)
		return(-1);

	if( (filters->acceptlinksrc= malloc(sizeof(struct ether_addr) * MAX_ACCEPT_LINK_SRC)) == NULL)
		return(-1);

	if( (filters->acceptlinkdst= malloc(sizeof(struct ether_addr) * MAX_ACCEPT_LINK_DST)) == NULL)
		return(-1);

	if( (filters->acceptsrclen= malloc(sizeof(u_int8_t) * MAX_ACCEPT_SRC)) == NULL)
		return(-1);

	if( (filters->acceptdstlen= malloc(sizeof(u_int8_t) * MAX_ACCEPT_DST)) == NULL)
		return(-1);

	if( (filters->accepttargetlen= malloc(sizeof(u_int8_t) * MAX_ACCEPT_TARGET)) == NULL)
		return(-1);

	return(0);
}
