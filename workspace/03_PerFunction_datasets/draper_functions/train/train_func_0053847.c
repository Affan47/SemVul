write_lease_option (struct option_cache *oc,
			 struct packet *packet, struct lease *lease,
			 struct client_state *client_state,
			 struct option_state *in_options,
			 struct option_state *cfg_options,
			 struct binding_scope **scope,
			 struct universe *u, void *stuff)
{
	const char *name, *dot;
	struct data_string ds;
	char *preamble = stuff;

	memset (&ds, 0, sizeof ds);

	if (u != &dhcp_universe) {
		name = u -> name;
		dot = ".";
	} else {
		name = "";
		dot = "";
	}
	if (evaluate_option_cache (&ds, packet, lease, client_state,
				   in_options, cfg_options, scope, oc, MDL)) {
		fprintf(leaseFile, "%soption %s%s%s %s;\n", preamble,
			name, dot, oc->option->name,
			pretty_print_option(oc->option, ds.data, ds.len,
					    1, 1));
		data_string_forget (&ds, MDL);
	}
}
