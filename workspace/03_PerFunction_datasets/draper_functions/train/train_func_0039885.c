print_sflow_counter_generic(const u_char *pointer, u_int len) {

    const struct sflow_generic_counter_t *sflow_gen_counter;

    if (len < sizeof(struct sflow_generic_counter_t))
	return 1;


    sflow_gen_counter = (const struct sflow_generic_counter_t *)pointer;
    printf("\n\t      ifindex %u, iftype %u, ifspeed %" PRIu64 ", ifdirection %u (%s)",
	   EXTRACT_32BITS(sflow_gen_counter->ifindex),
	   EXTRACT_32BITS(sflow_gen_counter->iftype),
	   EXTRACT_64BITS(sflow_gen_counter->ifspeed),
	   EXTRACT_32BITS(sflow_gen_counter->ifdirection),
	   tok2str(sflow_iface_direction_values, "Unknown",
		   EXTRACT_32BITS(sflow_gen_counter->ifdirection)));
    printf("\n\t      ifstatus %u, adminstatus: %s, operstatus: %s",
	   EXTRACT_32BITS(sflow_gen_counter->ifstatus),
	   EXTRACT_32BITS(sflow_gen_counter->ifstatus)&1 ? "up" : "down",
	   (EXTRACT_32BITS(sflow_gen_counter->ifstatus)>>1)&1 ? "up" : "down");
    printf("\n\t      In octets %" PRIu64
	   ", unicast pkts %u, multicast pkts %u, broadcast pkts %u, discards %u",
	   EXTRACT_64BITS(sflow_gen_counter->ifinoctets),
	   EXTRACT_32BITS(sflow_gen_counter->ifinunicastpkts),
	   EXTRACT_32BITS(sflow_gen_counter->ifinmulticastpkts),
	   EXTRACT_32BITS(sflow_gen_counter->ifinbroadcastpkts),
	   EXTRACT_32BITS(sflow_gen_counter->ifindiscards));
    printf("\n\t      In errors %u, unknown protos %u",
	   EXTRACT_32BITS(sflow_gen_counter->ifinerrors),
	   EXTRACT_32BITS(sflow_gen_counter->ifinunkownprotos));
    printf("\n\t      Out octets %" PRIu64
	   ", unicast pkts %u, multicast pkts %u, broadcast pkts %u, discards %u",
	   EXTRACT_64BITS(sflow_gen_counter->ifoutoctets),
	   EXTRACT_32BITS(sflow_gen_counter->ifoutunicastpkts),
	   EXTRACT_32BITS(sflow_gen_counter->ifoutmulticastpkts),
	   EXTRACT_32BITS(sflow_gen_counter->ifoutbroadcastpkts),
	   EXTRACT_32BITS(sflow_gen_counter->ifoutdiscards));
    printf("\n\t      Out errors %u, promisc mode %u",
	   EXTRACT_32BITS(sflow_gen_counter->ifouterrors),
	   EXTRACT_32BITS(sflow_gen_counter->ifpromiscmode));

    return 0;
}
