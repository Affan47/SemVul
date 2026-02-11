hsep_connection_init(struct gnutella_node *n, uint8 major, uint8 minor)
{
	static const hsep_ctx_t zero_hsep;
	time_t now = tm_time();
	uint i;

	g_assert(n);

	if (GNET_PROPERTY(hsep_debug) > 1)
		printf("HSEP: Initializing node %s\n",
			host_addr_port_to_string(n->addr, n->port));

	WALLOC(n->hsep);
	*n->hsep = zero_hsep;
	n->hsep->last_sent = now;
	n->hsep->major = major;
	n->hsep->minor = minor;


	for (i = 1; i < G_N_ELEMENTS(hsep_global_table); i++) {
		n->hsep->table[i][HSEP_IDX_NODES] = 1;
		hsep_global_table[i][HSEP_IDX_NODES]++;
	}


	hsep_sanity_check();

	hsep_fire_global_table_changed(now);
}
