parse_net_name(struct dvb_v5_fe_parms *parms, struct nit_table *nit_table,
		const unsigned char *buf, int dlen, int verbose)
{
	parse_string(parms, &nit_table->network_name, &nit_table->network_alias,
			&buf[2], dlen, default_charset, output_charset);
	if (verbose) {
		printf("Network");
		if (nit_table->network_name)
			printf(" %s", nit_table->network_name);
		if (nit_table->network_alias)
			printf(" (%s)", nit_table->network_alias);
		if (!nit_table->network_name && !nit_table->network_alias)
			printf(" unknown");
		printf("\n");
	}
}
