ipv4_fragment_expired ( struct retry_timer *timer,
				    int fail __unused ) {
	struct ipv4_fragment *frag =
		container_of ( timer, struct ipv4_fragment, timer );
	struct iphdr *iphdr = frag->iobuf->data;

	DBGC ( iphdr->src, "IPv4 fragment %04x expired\n",
	       ntohs ( iphdr->ident ) );
	free_iob ( frag->iobuf );
	list_del ( &frag->list );
	free ( frag );
}
