search_subencapsulation(struct data_string *result, struct packet *packet,
			struct lease *lease, struct client_state *client_state,
			struct option_state *in_options,
			struct option_state *cfg_options,
			struct binding_scope **scope,
			struct universe *universe)
{
	struct data_string sub;
	struct universe *subu;
	int i, status = 0;

	memset(&sub, 0, sizeof(sub));
	for (i = 0 ; i < cfg_options->universe_count ; i++) {
		subu = universes[i];

		if (subu == NULL)
			log_fatal("Impossible condition at %s:%d.", MDL);

		if (subu->enc_opt != NULL &&
		    subu->enc_opt->universe == universe &&
		    subu->enc_opt->format != NULL &&
		    subu->enc_opt->format[0] == 'E' &&
		    lookup_option(universe, cfg_options,
				  subu->enc_opt->code) == NULL &&
		    subu->encapsulate(&sub, packet, lease, client_state,
				      in_options, cfg_options,
				      scope, subu)) {
			if (append_option(result, universe,
					  subu->enc_opt, &sub))
				status = 1;

			data_string_forget(&sub, MDL);
		}
	}

	return status;
}
